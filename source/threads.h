#ifndef THREADS
#define THREADS

#include <stdio.h>
#include "matriz.h"

struct Parametros {
    int matriz1_N, matriz2_N;
    int matriz1_i;
    float **matriz1;
    float **matriz2;
    float **tensorial;
}typedef Parametros;

void *thread_por_linha(void *arg);

void calcular_tensorial_threads(Node *head);

#endif