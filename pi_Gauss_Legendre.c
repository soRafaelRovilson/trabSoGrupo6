#include <stdio.h>
#include <math.h>

#define INTERACOES 1000



double calculo_aN(double aN, double bN){
    aN = (aN + bN)/2;

    return aN;
}

double calculo_tN(int pN, double tN, double aN_anterior, double aN){
    tN = tN - pN*(aN_anterior - aN)*(aN_anterior - aN);

    return tN;
}

int calculo_pN(int pN){
    pN = 2*pN;

    return pN;
}

double calculo_bN(double aN_anterior, double bN){
    bN = sqrt(aN_anterior*bN);

    return bN;
}

double calculo_pi(double aN, double bN, double tN){
    double pi;
    pi = ((aN + bN)*(aN + bN))/(4*tN);

    return pi;
}


int main(){

    int i;

    // Declarando os valores iniciais referentes ao
    // método de Gauss-Legendre (N=0)

    int pN = 1;
    double aN = 1,
           tN = 1.0/4.0,
           bN = 1.0/sqrt(2);
    double aN_anterior, pi;


    //calculo de pi


    for(i=0 ; i < INTERACOES; i++){
        aN_anterior = aN;

        aN = calculo_aN(aN, bN);
        tN = calculo_tN(pN, tN, aN_anterior, aN);
        pN = calculo_pN(pN);
        bN = calculo_bN(aN_anterior, bN);
        pi = calculo_pi(aN, bN, tN);

        //printf("%.6f\n", pi);

    }
    printf("%.6f\n\n", pi);


}

