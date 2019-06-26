

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#define NTHREADS 10

typedef struct{
  int size;
  double S, E, r, sigma, T;
  double *trials;
  double soma;
  double tempo;
}entrada;

struct EstruturaAleatorio{
  double x1, x2, w, y1, y2;
  int useLast;
  struct drand48_data random;
};

/*Inicialização do gerador de números aleatórios*/
void geraValor(struct EstruturaAleatorio* state){
  state->random.__init = 0;
  state->useLast = 0;
        
  struct timeval now;
  gettimeofday(&now, NULL);
  state->random.__x[0] = now.tv_usec;
}

/*Geração de números aleatórios*/
double RandomNumber(struct EstruturaAleatorio* state){
  if (state->useLast){
    state->y1 = state->y2;
    state->useLast = 0;
  }else{
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

/*Calcula: Desvio Padrão*/
double stdDev(double trials[], double mean, int M){
  double stddev = 0.0;
  int i;
  for(i = 0; i < M; i++){
    stddev += pow((trials[i] - mean),2);
  }
  stddev = sqrt(stddev/((double)M-1));
  return stddev;
}


void *BlackScholeParalelo_Calculo(void *ptr){

  entrada *tipoEntrada = (entrada*) ptr;

  int i;
  double t;
  struct EstruturaAleatorio state;

  geraValor(&state);

  tipoEntrada->soma = 0;

  for(i = 0; i < tipoEntrada->size; i++){
    t = tipoEntrada->S*exp((tipoEntrada->r-((1.0/2.0)*pow(tipoEntrada->sigma, 2.0)))*tipoEntrada->T + tipoEntrada->sigma*sqrt(tipoEntrada->T)*RandomNumber(&state));
    if((t-tipoEntrada->E) > 0.0)
      tipoEntrada->trials[i] = exp((-tipoEntrada->r)*tipoEntrada->T)*(t-tipoEntrada->E);
    else
      tipoEntrada->trials[i] = 0.0;
    tipoEntrada->soma += tipoEntrada->trials[i];
  }
  return NULL;
}

void BlackScholeParalelo(double S, double E, double r, double sigma, double T, int M, double Tempo){

  pthread_t thread[NTHREADS];

  double t,resultado = 0.0, trials[M], mean, stddev, confwidth, confmin, confmax;

  int retorno[NTHREADS], i, j, count;
  entrada *tipoEntrada[NTHREADS];

  /*Cria e inicializa as threads*/
  for(i = 0; i < NTHREADS; i++){	
    tipoEntrada[i] = (entrada *)calloc(1, sizeof(entrada));
    tipoEntrada[i]->S = S;
    tipoEntrada[i]->E = E;
    tipoEntrada[i]->r = r;
    tipoEntrada[i]->sigma = sigma;
    tipoEntrada[i]->T = T;
    tipoEntrada[i]->size = (M/(double)NTHREADS);
    tipoEntrada[i]->trials = (double*)calloc(tipoEntrada[i]->size, sizeof(double));

    retorno[i] = pthread_create(&thread[i], NULL, BlackScholeParalelo_Calculo, (void*) tipoEntrada[i]);
    if(retorno[i]){
      fprintf(stderr,"Erro - pthread_create(): %d\n",retorno[i]);
      exit(EXIT_FAILURE);
    }
  }

  for(i = 0; i < NTHREADS; i++){
    pthread_join(thread[i], NULL);
  }

  count = 0;
	
  for(i = 0; i < NTHREADS; i++){
    resultado+=tipoEntrada[i]->soma;
    for(j = 0; j < tipoEntrada[i]->size; j++){
      trials[count++] = tipoEntrada[i]->trials[j];
    }
    free(tipoEntrada[i]->trials);
    free(tipoEntrada[i]);
  }
	
  mean = resultado/(double)M;
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
  printf("Tempo de execu��o: %lf\n", Tempo);
  printf("Intervalo de Confianca = (%lf, %lf)\n", confmin, confmax);	

  pthread_exit(NULL);
  exit(EXIT_SUCCESS);

}

int main(){



 struct EstruturaAleatorio
  {
        double x1, x2, w, y1, y2;
        int useLast;
        struct drand48_data random;
  };



  double S, E, r, sigma, T, Tempo;

  int M;
  
 
	
//Atruibuicao de valores
	
  S = 100;
  E = 100;
  r = 0.05;
  sigma = 0.2;
  T = 1;
  M = 1000;


  	clock_t Ticks[2];
    Ticks[0] = clock();
    
  BlackScholeParalelo(S, E, r, sigma, T, M,Tempo);
  
	Ticks[1] = clock();
    Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    
  return 0;
}
