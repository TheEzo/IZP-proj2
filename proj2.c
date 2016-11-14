#include <stdio.h>
#include <math.h>

double taylor_log(double x, unsigned int n);
double cfrac_log(double x, unsigned int n);
double taylor_pow(double x, double y, unsigned int n);
double taylorcf_pow(double x, double y, unsigned int n);

double mylog(double x);
double mypow(double x, double y);


double ezpow(double x, unsigned int n){
    double vysledek = 1;
    for(unsigned int i = 0; i < n; i++){
        vysledek *= x;
    }
    return vysledek;
}

double pi(unsigned int n){
    double vysledek = 0;
    unsigned int z = 1;
    for(unsigned int i = 0; i < n; i++){
        vysledek = ezpow(z, 2) / (6 + vysledek);
        z += 2;
    }

    return 3 + 1/vysledek;
}

double sqrt_2(unsigned int n){
    double vysledek = 0;
    for(int i = 0; i < n; i++)
        vysledek = 1.0/ (2 + vysledek);

    return 1 + vysledek;
}


int main() {
    printf("%.12g\n", taylor_log(0.1, 1000));
    printf("%.12g\n", log(0.1));
    printf("%.12g\n", cfrac_log(0.1, 1000));
    //printf("**************************************\n\n");
    //printf("%.12g\n", sqrt_2(1000));
    //printf("%.12g\n", pi(10000));
    return 0;
}

double taylor_log(double x, unsigned int n){
    unsigned int i;
    double pom = 0;
    double vysledek = 0;
    if(x <= 1) {
        x = 1-x;
        for (i = 1; i < n + 1; i++) {
            pom = ezpow(x, i) / i;
            vysledek -= pom;
            if (pom == 0)
                break;
        }
    }
    else{
        for(i = 1; i < n + 1; i++){
            pom = ezpow((x-1)/x, i) / i;
            if(pom == 0)
                break;
            vysledek += pom;

        }
    }
    return vysledek;
}

double cfrac_log(double x, unsigned int n){
    double vysledek = 0;
    x = (x - 1) / (x + 1);
    unsigned int cislo = 2 * n + 1;
    for(unsigned int i = n; i > 0 && cislo >= 3; i--){
        //printf("%gz^2 / (%d - %.12g)\n", ezpow(i, 2), cislo, vysledek);
        vysledek = (ezpow(i, 2) * ezpow(x, 2)) / (cislo - vysledek);
        //printf("%d,%d       ", i, cislo);
        cislo -= 2;
    }
    return (2 * x)/ (1 - vysledek);

    /*//double z = (x - 1)/(x + 1);
    double vysledek = 0;
    double z = (1 + x) / (1 - x);
    unsigned int prvni_cislo = 3;
    for(unsigned int i = 1; i < n + 1; i++){
        vysledek = (ezpow(i, 2) * ezpow(z, 2)) / (prvni_cislo - vysledek);
        prvni_cislo += 2;
    }
    //vysledek = (2 * z) / (1 - vysledek);
    vysledek = (1 + vysledek) / (1 - vysledek);*/
    return vysledek;
}
/*
double taylor_pow(double x, double y, unsigned int n){

}

double taylorcf_pow(double x, double y, unsigned int n){

}



double mylog(double x){

}

double mypow(double x, double y){
    double vysledek = 0;
    
}*/