#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define INTERACOES 1000

int pN = 1;
double aN = 1,
       tN = 1.0/4.0,
       bN = 1.0/sqrt(2);
double aN_anterior;



double *calculo_aN(void *arg){
    aN = (aN + bN)/2;
    //printf("aN: %f\n", aN);

    //tN = calculo_tN();

    //return aN;
}

double calculo_tN(){
    tN = tN - pN*(aN_anterior - aN)*(aN_anterior - aN);

    return tN;
}

int *calculo_pN(void *arg){
    pN = 2*pN;

    //return pN;
}

double *calculo_bN(void *arg){
    bN = sqrt(aN_anterior*bN);

    //return bN;
}

double calculo_pi(){
    double pi;
    pi = ((aN + bN)*(aN + bN))/(4*tN);

    return pi;
}

int main(){
    pthread_t thread_aN, thread_bN, thread_tN, thread_pN;
    int i;
    double pi;

    for(i=0; i<INTERACOES ; i++){
        aN_anterior = aN;

        pthread_create(&thread_aN, NULL, calculo_aN, NULL);
        pthread_create(&thread_pN, NULL, calculo_pN, NULL);
        pthread_create(&thread_bN, NULL, calculo_tN, NULL);

        pthread_join(thread_aN, NULL);
        pthread_join(thread_pN, NULL);
        pthread_join(thread_bN, NULL);

        tN = calculo_tN();
        pi = calculo_pi();

    }
    printf("%f\n", pi);
}

