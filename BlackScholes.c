

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<time.h>

struct EstruturaAleatorio{
    double x1, x2, w, y1, y2;
    int useLast;
    struct drand48_data random;
};


void geraValor(struct EstruturaAleatorio* state){
    state->random.__init = 0;
    state->useLast = 0;
        
    struct timeval now;
    state->random.__x[0] = now.tv_usec;
}

double RandomNumber(struct EstruturaAleatorio* state){
    if (state->useLast){
        state->y1 = state->y2;
        state->useLast = 0;
    }
  else{
        do{
            drand48_r(&state->random, &state->x1);
            state->x1 = 2.0 * state->x1 - 1.0;
            drand48_r(&state->random, &state->x2);
            state->x2 = 2.0 * state->x2 - 1.0;
            state->w = state->x1 * state->x1 + state->x2 * state->x2;
        }
        while (state->w >= 1.0);
            state->w = sqrt((-2.0 * log(state->w)) / state->w);
            state->y1 = state->x1 * state->w;
            state->y2 = state->x2 * state->w;
            state->useLast = 1;
    }
    return state->y1;
}


double stdDev(double trials[], double mean, int M){
    double stddev = 0.0;
    int i;
    for(i = 0; i < M; i++){
        stddev += pow((trials[i] - mean),2);
    }
    stddev = sqrt(stddev/((double)M-1));
    return stddev;
}


int blackScholes(double S, double E, double r, double sigma, double T, int M){
    int i;
    double t, mean = 0.0, stddev, confwidth, confmin, confmax;
    double *trials;

    trials = (double *) malloc(M*sizeof(double));

    struct EstruturaAleatorio state;
    geraValor(&state);



    for(i = 0; i < M; i++){
        t = S*exp((r-((1.0/2.0)*pow(sigma, 2.0)))*T + sigma*sqrt(T)*RandomNumber(&state));

        if((t-E) > 0.0)
            trials[i] = exp((-r)*T)*(t-E);
        else
            trials[i] = 0.0;
    mean += trials[i];
    }


    mean = mean/(double)M;
    stddev = stdDev(trials, mean, M);
    confwidth = 1.96*stddev/sqrt(M);
    confmin = mean - confwidth;
    confmax = mean + confwidth;
    
    printf("S = %lf\n", S);
    printf("E = %lf\n", E);
    printf("r = %lf\n", r);
    printf("sigma = %lf\n", sigma);
    printf("T = %lf\n", T);
    printf("M = %d\n", M);
    printf("Media = %lf\n", mean);
    printf("Desvio Padrao = %lf\n", stddev);
    printf("Tempo Execucao = %lf\n", t);
    printf("Intervalo de Confianca = (%lf, %lf)\n", confmin, confmax);

    return 0;

}

int main(char **argv){

    double resp;

     FILE *saida;
    saida = fopen("tempo.txt", "a");

	
    double S = 100; 
    double E = 100; 
    double r = 0.05; 
    double sigma = 0.2; 
    double T = 1; 
    int M = 1000;
    
	clock_t start_t, end_t;
    double total_t;
    start_t = clock(); 

    blackScholes(S, E, r, sigma, T, M);
    
    end_t = clock(); //Coleta Final
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    fprintf(saida, "%f\n", total_t);
    return 0;
}
