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

int kontrola_pow(double x, double y);

void chyba(); /* chybovy vystup */

int main(int argc, char **argv) {
    double x = 0;
    double y = 0;
    unsigned int n = 0;
    /* promenna pro kontrolu spravnosti zadaneho cisla */
    char *end_ptr_x = NULL;
    char *end_ptr_y = NULL;
    char *end_ptr_n = NULL;

    if(argc == 4 && !strcmp(argv[1], "--log")){
        x = strtod(argv[2], &end_ptr_x);
        n = strtoul(argv[3], &end_ptr_n, 10);
        if(*end_ptr_n == 0 && *end_ptr_x == 0){
            printf("       log(%g) = %.12g\n", x, log(x));
            printf(" cfrac_log(%g) = %.12g\n", x, cfrac_log(x, n));
            printf("taylor_log(%g) = %.12g\n", x, taylor_log(x, n));
        }
        else
            chyba();
    }
    else if (argc == 5 && !strcmp(argv[1], "--pow")){
        n = strtoul(argv[4], &end_ptr_n, 10);
        x = strtod(argv[2], &end_ptr_x);
        y = strtod(argv[3], &end_ptr_y);
        if(*end_ptr_n == 0 && *end_ptr_x == 0 && *end_ptr_y == 0) {
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
    /* osetreni vstupu se kteryma funkce neni schopna pocitat a matematicke definice */
    if(x == 0)
        return -INFINITY;
    if(x == INFINITY)
        return INFINITY;
    if(x == -INFINITY || x < 0)
        return NAN;
    unsigned int i;
    double pom = 0;
    double vysledek = 0, pom_x = 1;
    if(x <= 1) {/*doporucena mezni hodnota ze zadani */
        /* vyjadreni x ze vzorce */
        x = 1 - x;
        /* implementace vzorce */
        pom_x = x / 1;
        vysledek -= pom_x;
        for (i = 2; i < n + 1; i++) {
            pom_x *= (i - 1) * x / i;
            vysledek -= pom_x;
        }
    }
    else{
        /* implementace vzorce */
        for(i = 1; i < n + 1; i++){
            pom_x *= (x-1) / x;
            pom = pom_x / i;
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
    /* osetreni vstupu se kteryma funkce neni schopna pocitat a matematicke definice */
    if(x == 0)
        return -INFINITY;
    if(x == INFINITY)
        return INFINITY;
    if(x == -INFINITY || x < 0)
        return NAN;

    double vysledek = 0;
    /* vyjadreni x ze vzorce */
    x = (x - 1) / (x + 1);
    unsigned int cislo = 2 * n + 1;
    double pow_x = x*x;
    /* implementace vzorce */
    for(unsigned int i = n; i > 0 && cislo >= 3; i--){
        vysledek = i*i * pow_x / (cislo - vysledek);
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
    /* osetreni vstupu se kteryma funkce neni schopna pocitat a matematicke definice */
    if(x < 1 && x > 0 && y == INFINITY)
        return 0;
    if(x < 1 && x > 0 && y == -INFINITY)
        return INFINITY;
    if(x < 0 && x > -1 && y == INFINITY)
        return 0;
    if((x == INFINITY || x == -INFINITY) && y > 0)
        return INFINITY;
    if(x != 0 && y == INFINITY)
        return INFINITY;
    if(x < 0)
        return NAN;
    if(x == 1)
        return 1;
    if(x == 0 && y <= 0)
        return INFINITY;
    if(x == 0 && y > 0)
        return 0;
    if(x != 0 && y == 0)
        return 1;
    if(y == INFINITY || y == -INFINITY || y == NAN || y == -NAN || x == INFINITY || x == -INFINITY ||
       x == NAN || x == -NAN)
        return kontrola_pow(x,y);


    double vysledek = 0, pom = 1;
    /* ulozeni vysledku do promenne kvuli optimalizace */
    x = taylor_log(x, n);
    /* implementace vzorce */
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
    /* osetreni vstupu se kteryma funkce neni schopna pocitat a matematicke definice */
    if(x < 1 && x > 0 && y == INFINITY)
        return 0;
    if(x < 1 && x > 0 && y == -INFINITY)
        return INFINITY;
    if(x < 0 && x > -1 && y == INFINITY)
        return 0;
    if((x == INFINITY || x == -INFINITY) && y > 0)
        return INFINITY;
    if(x != 0 && y == INFINITY)
        return INFINITY;
    if(x < 0)
        return NAN;
    if(x == 1)
        return 1;
    if(x == 0 && y <= 0)
        return INFINITY;
    if(x == 0 && y > 0)
        return 0;
    if(x != 0 && y == 0)
        return 1;
    if(y == INFINITY || y == -INFINITY || y == NAN || y == -NAN || x == INFINITY || x == -INFINITY ||
        x == NAN || x == -NAN)
        return kontrola_pow(x,y);



    double vysledek = 0, pom = 1;
    /* ulozeni vysledku do promenne kvuli optimalizace */
    x = cfrac_log(x, n);
    /* implementace vzorce */
    for(unsigned int i = 1; i <= n; i++){
        pom *= y * x / i;
        vysledek += pom;
    }
    return 1 + vysledek;
}


void chyba(){
    printf("Spatne zadane parametry.\n");
}

/**
 * doplnujici kontrolni funkce
 * @param x
 * @param y
 * @return - chybovy stav
 */
int kontrola_pow(double x, double y){
    if((x == 1 || x == -1) && (y == INFINITY || y == -INFINITY))
        return 1;
    if(y == NAN && x == 1)
        return 1;
    if(x == 0 && y == INFINITY)
        return 0;
    if(x == NAN || x == -NAN)
        return NAN;
    if(x == INFINITY && y < 0)
        return 0;
    if(x == INFINITY && y > 0)
        return INFINITY;

    return 0;
}