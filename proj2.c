/****************************************************/
/* * *       Projekt 2 - Iterační výpočty       * * */
/* * *                                          * * */
/* * *             Tomáš Willaschek             * * */
/* * *                 xwilla00                 * * */
/* * *             1BIB - 2016/2017             * * */
/****************************************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

double taylor_log(double x, unsigned int n);
double cfrac_log(double x, unsigned int n);
double taylor_pow(double x, double y, unsigned int n);
double taylorcf_pow(double x, double y, unsigned int n);

int is_number(char * x);
int parametr_n(char *x);

double mylog(double x);
double mypow(double x, double y);

void chyba();

int main(int argc, char **argv) {
    double x = 0;
    unsigned int n = 0;
    if(argc == 4 && !strcmp(argv[1], "--log")){
        if(is_number(argv[2]) && parametr_n(argv[3])) {
            x = strtod(argv[2], NULL);
            n = strtoul(argv[3], NULL, 10);
            printf("       log(%g) = %.12g\n", x, log(x));
            printf(" cfrac_log(%g) = %.12g\n", x, cfrac_log(x, n));
            printf("taylor_log(%g) = %.12g\n", x, taylor_log(x, n));
        }
        else
            chyba();
    }
    else if (argc == 5 && !strcmp(argv[1], "--pow")){
        if(is_number(argv[2]) && is_number(argv[3]) && parametr_n(argv[4])){
            n = strtoul(argv[4], NULL, 10);
            x = strtod(argv[2], NULL);
            double y = strtod(argv[3], NULL);
            printf("         pow(%g,%g) = %.12g\n", x, y, pow(x, y));
            printf("  taylor_pow(%g,%g) = %.12g\n", x, y, taylor_pow(x, y, n));
            printf("taylorcf_pow(%g,%g) = %.12g\n", x, y, taylorcf_pow(x, y, n));

        }
        else{
            chyba();
        }
    }
    else
        printf("Parametry programu nebyly zadane spravne.\n");

    return 0;
}


/**
 * Tayloruv logaritmus
 * @param x - vstupni hodnota logaritmu
 * @param n - udava rozvoj polynomu
 * @return - vraci vysledek [log(x)]
 */
double taylor_log(double x, unsigned int n){
    if(x == 0)
        return -INFINITY;
    if(x < 0)
        return NAN;
    unsigned int i;
    double pom = 0;
    double vysledek = 0, pow_x = 1;
    if(x <= 1) {
        x = 1-x;
        for (i = 1; i < n + 1; i++) {
            pow_x *= x;
            pom = pow_x / i;
            vysledek -= pom;
        }
    }
    else{
        for(i = 1; i < n + 1; i++){
            pow_x *= (x-1) / x;
            pom = pow_x / i;
            vysledek += pom;
        }
    }
    return vysledek;
}

/**
 * Logaritmus reseny pomoci zretezeneho zlomku
 * @param x - hodnota, ze ktere se pocita logaritmus
 * @param n - udava rozvoj polynomu
 * @return - vraci vysledek [log(x)]
 */
double cfrac_log(double x, unsigned int n){
    if(x == 0)
        return -INFINITY;
    if(x < 0)
        return NAN;
    double vysledek = 0;
    x = (x - 1) / (x + 1);
    unsigned int cislo = 2 * n + 1;
    for(unsigned int i = n; i > 0 && cislo >= 3; i--){
        vysledek = (i*i * x*x) / (cislo - vysledek);
        cislo -= 2;
    }
    return (2 * x)/ (1 - vysledek);

}

/**
 * Mocninna funkce resena pomoci taylorova logaritmu, x^y
 * @param x
 * @param y
 * @param n - udava rozvoj polynomu
 * @return - vysledek x^y
 */
double taylor_pow(double x, double y, unsigned int n){
    double vysledek = 0, pom = 1;
    x = taylor_log(x, n);
    for(unsigned int i = 1; i <= n; i++){
        pom *= y * x / i;
        vysledek += pom;
    }

    return 1 + vysledek;
}

/**
 * Mocninna funkce resena pomoci zretezeneho zlomku, x^y
 * @param x
 * @param y
 * @param n  - udava rozvoj polynomu
 * @return - vysledek x^y
 */
double taylorcf_pow(double x, double y, unsigned int n){
    double vysledek = 0, pom = 1;
    x = cfrac_log(x, n);
    for(unsigned int i = 1; i <= n; i++){
        pom *= y * x / i;
        vysledek += pom;
    }
    return 1 + vysledek;
}
/*


double mylog(double x){

}

double mypow(double x, double y){
    double vysledek = 0;
    
}*/



void chyba(){
    printf("Spatne zadane parametry.\n");
}

int is_number(char *x){
    if(!strcmp(x, "nan") || !strcmp(x, "-nan") || !strcmp(x, "inf") || !strcmp(x, "-inf"))
        return 1;
    if(x[0] != '-' || !(x[0] <= '9' || x[0] >= '0'))                        //x[0] != 'e' || x[0] != '+')
        return 0;
    int tecka = 0;
    for(unsigned int i = 1; i < strlen(x); i++){

    }
    /*
    if(!strcmp(x, "nan") || !strcmp(x, "-nan") || !strcmp(x, "inf") || !strcmp(x, "-inf"))
        return 1;
    int tecka = 0;
    if(x[0] != '-' || x[0] > '9' || x[0] < '0')                        //x[0] != 'e' || x[0] != '+')
        return 0;
    for(unsigned int i = 1; i < strlen(x); i++) {
        if (x[i] == '.')
            tecka++;
        else if (x[i] < '0' || x[i] > '9')
            return 0;
        else if (!(x[i] == 'e' && (x[i+1] == '+' || x[i+1] == '-')))
            return 0;
    }
    if(tecka <= 1)
        return 1;
    printf("Here\n");
    return 0;
     */
}

int parametr_n(char *x){
    for(unsigned int i = 0; i < strlen(x); i++)
        if(x[i] < '0' || x[i] > '9')
            return 0;
    return 1;
}