#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define INTERACOES 1000000000
#define NTHREADS 100

int parcela = INTERACOES/NTHREADS;
int count[NTHREADS];


float *calculo_dentro(void *arg){
    int *valor = (int *)(arg);
    int dentro = 0;
    int N;
    float x, y, tamanho, aux, razao;

    for(N=1 ; N <= parcela ; N++){
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
    count[*valor] = dentro;
    return dentro;
}

int main(){
    pthread_t threads[NTHREADS];
    double pi;
    int dentro, i;

    for(i=0; i<NTHREADS; i++){
        pthread_create(&threads[i], NULL, calculo_dentro, (void *)(&i));
    }

    for(i=0; i<NTHREADS; i++){
        pthread_join(threads[i], NULL);
    }

    for(i=0; i<NTHREADS; i++){
        dentro += count[i];
        printf("%d\n", dentro);
    }

    pi = 4*((float)dentro/INTERACOES);
    printf("%.6f\n", pi);

}
