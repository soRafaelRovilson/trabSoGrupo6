#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define INTERACOES 1000000000


float calculo_dentro(int interacoes){

    int dentro = 0;
    int N;
    float x, y, tamanho, aux, razao;

    for(N=1 ; N <= interacoes ; N++){
        x = ((rand()%101));
        x = x / 100;
        y = ((rand()%101));
        y = y / 100;
        aux = pow(x,2)+pow(y,2);
        tamanho = sqrt(aux);
        if(tamanho <= 1)
            dentro = dentro + 1;
        //printf("dentro = %d e total = %d\n\n", dentro, N);
    }
    return dentro;
}

int main(){
    double pi;
    int dentro;



    dentro = calculo_dentro(INTERACOES);



    //printf("dentro = %d e total = %d\n\n", dentro, total);
    pi = 4*((float)dentro/INTERACOES);
    printf("%.6f\n", pi);

}
