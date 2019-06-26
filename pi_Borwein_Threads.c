#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define INTERACOES 500

//Declarando as variáveis iniciais

double aN = 6.0 - 4.0*sqrt(2),
       yN = sqrt(2) - 1.0;

// Variaveis para o calculo de pi

double pi,
       subtrai,
       soma,
       parte_1,
       parte_2,
       aN_anterior,
       parte_a,
       parte_b,
       parte_1_a,
       parte_1_b;
int expoente_2;
int base = 2;
float expoente = 0.25;


double *calculo_pi(void *arg){
    pi = 1 / aN_anterior;

    //return pi;
}

double *obtendo_subtrai(void *arg){
    subtrai = (1 - pow(yN, 4));

    //return subtrai;
}

double *obtendo_soma(void *arg){
    soma = (1 + pow(yN, 4));

    //return soma;
}

double *obtendo_parte_a(void *arg){
    parte_a = pow(subtrai, expoente);

    //return parte_a;
}

double *obtendo_parte_b(void *arg){
    parte_b = pow(soma, expoente);

    //return parte_b;
}

double calculo_yN(){
    yN = (1 - parte_a)/(1 + parte_b);

    return yN;
}

double *obtendo_parte_1(void *arg){
    parte_1 = 1 + yN;

    //return parte_1;
}

double *obtendo_parte_2(void *arg){
    parte_2 = 1 + yN + pow(yN,2);

    //return parte_2;
}

double *obtendo_expoente_2(void *arg){
    int *valor = (int *)(arg);

    expoente_2 = 2*(*valor) + 1;

    //return expoente_2;
}

double *obtendo_parte_1_a(void *arg){
    parte_1_a = aN*pow(parte_1,4);

    //return parte_1_a;

}

double *obtendo_parte_1_b(void *arg){
    parte_1_b = pow(base,expoente_2)*yN*parte_2;

    //return parte_1_b;
}



int main(){


    int N;

    // Calculo de pi

    for(N=1 ; N <= INTERACOES ; N++){
        pthread_t t_pi, t_subtrai, t_soma, t_parte_a, t_parte_b, t_parte_1, t_parte_2, t_expoente_2, t_parte_1_a, t_parte_1_b;
        aN_anterior = aN;

        // calculo yN seguinte

        //
        pthread_create(&t_pi, NULL, calculo_pi, NULL);
        pthread_create(&t_subtrai, NULL, obtendo_subtrai, NULL);
        pthread_create(&t_soma, NULL, obtendo_soma, NULL);

        pthread_join(t_pi, NULL);
        pthread_join(t_subtrai, NULL);
        pthread_join(t_soma, NULL);

        //
        pthread_create(&t_parte_a, NULL, obtendo_parte_a, NULL);
        pthread_create(&t_parte_b, NULL, obtendo_parte_b, NULL);

        pthread_join(t_parte_a, NULL);
        pthread_join(t_parte_b, NULL);

        //

        yN = calculo_yN();

        // calculo de aN seguinte

        //
        pthread_create(&t_parte_1, NULL, obtendo_parte_1, NULL);
        pthread_create(&t_parte_2, NULL, obtendo_parte_2, NULL);
        pthread_create(&t_expoente_2, NULL, obtendo_expoente_2, (void *)(&N));

        pthread_join(t_parte_1, NULL);
        pthread_join(t_parte_2, NULL);
        pthread_join(t_expoente_2, NULL);

        //
        pthread_create(&t_parte_1_a, NULL, obtendo_parte_1_a, NULL);
        pthread_create(&t_parte_1_b, NULL, obtendo_parte_1_b, NULL);

        pthread_join(t_parte_1_a, NULL);
        pthread_join(t_parte_1_b, NULL);

        //

        aN = parte_1_a - parte_1_b;
    }

    printf("%.6f\n", pi);

}
