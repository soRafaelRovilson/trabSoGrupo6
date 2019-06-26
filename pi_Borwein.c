#include <stdio.h>
#include <math.h>

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


double calculo_pi(){
    pi = 1 / aN_anterior;

    return pi;
}

double obtendo_subtrai(){
    subtrai = (1 - pow(yN, 4));

    return subtrai;
}

double obtendo_soma(){
    soma = (1 + pow(yN, 4));

    return soma;
}

double obtendo_parte_a(){
    parte_a = pow(subtrai, expoente);

    return parte_a;
}

double obtendo_parte_b(){
    parte_b = pow(soma, expoente);

    return parte_b;
}

double calculo_yN(){
    yN = (1 - parte_a)/(1 + parte_b);

    return yN;
}

double obtendo_parte_1(){
    parte_1 = 1 + yN;

    return parte_1;
}

double obtendo_parte_2(){
    parte_2 = 1 + yN + pow(yN,2);

    return parte_2;
}

double obtendo_expoente_2(int N){
    expoente_2 = 2*N + 1;

    return expoente_2;
}

double obtendo_parte_1_a(){
    parte_1_a = aN*pow(parte_1,4);

    return parte_1_a;

}

double obtendo_parte_1_b(){
    parte_1_b = pow(base,expoente_2)*yN*parte_2;

    return parte_1_b;
}



int main(){


    int N;

    // Calculo de pi

    for(N=1 ; N <= INTERACOES ; N++){
        aN_anterior = aN;
        pi = calculo_pi();

        // calculo yN seguinte

        subtrai = obtendo_subtrai();
        soma = obtendo_soma();

        parte_a = obtendo_parte_a();
        parte_b = obtendo_parte_b();

        yN = calculo_yN();

        // calculo de aN seguinte

        parte_1 = obtendo_parte_1();
        parte_2 = obtendo_parte_2();
        expoente_2 = obtendo_expoente_2(N);

        parte_1_a = obtendo_parte_1_a();
        parte_1_b = obtendo_parte_1_b();

        aN = parte_1_a - parte_1_b;
    }

    printf("%.6f\n", pi);

}
