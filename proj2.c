#include <stdio.h>
#include <math.h>

double taylor_log(double x, unsigned int n);
double cfrac_log(double x, unsigned int n);
double taylor_pow(double x, double y, unsigned int n);
double taylorcf_pow(double x, double y, unsigned int n);

double mylog(double x);
double mypow(double x, double y);


int main() {
    double x = 1.131401114526;
    printf("%.12g\n", log(x));
    printf("%.12g\n", cfrac_log(x, 4));
    printf("%.12g\n", taylor_log(x, 4));
    printf("**************\n");
    printf("%.12g\n", pow(1.23, 4.2));
    printf("%.12g\n", taylor_pow(1.23, 4.2, 4));
    printf("%.12g\n", taylorcf_pow(1.23, 4.2, 4));
    return 0;
}

double taylor_log(double x, unsigned int n){
    unsigned int i;
    double pom = 0;
    double vysledek = 0, pow_x = 1;
    if(x <= 1) {
        x = 1-x;
        for (i = 1; i < n + 1; i++) {
            pow_x *= x;
            pom = pow_x / i;
            vysledek -= pom;
            if (pom == 0)
                break;
        }
    }
    else{
        for(i = 1; i < n + 1; i++){
            pow_x *= (x-1) / x;
            pom = pow_x / i;
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
        vysledek = (i*i * x*x) / (cislo - vysledek);
        cislo -= 2;
    }
    return (2 * x)/ (1 - vysledek);

}

double taylor_pow(double x, double y, unsigned int n){
    double vysledek = 0, pom, pow_y = 1, pow_log = 1;
    for(unsigned int i = 1; i <= n; i++){
        pow_y *= y;
        pow_log *= taylor_log(x, n);
        pom = pow_y * pow_log;
        for(unsigned int j = i; j > 1; j--)
            pom /= j;
        vysledek += pom;
    }

    return 1 + vysledek;
}

double taylorcf_pow(double x, double y, unsigned int n){
    double vysledek = 0, pom;
    double pow_y = 1, pow_log = 1;
    for(unsigned int i = 1; i <= n; i++){
        pow_y *= y;
        pow_log *= cfrac_log(x, n);
        pom = pow_y * pow_log;
        for(unsigned int j = i; j > 1; j--)
            pom /= j;
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
