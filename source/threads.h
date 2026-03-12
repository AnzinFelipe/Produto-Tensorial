#ifndef THREADS
#define THREADS

#include <stdio.h>
#include "matriz.h"

struct Parametros {
    int matriz2_N;
    float matriz1_num;
    int matriz1_i, matriz1_j;
    float **matriz2;
    float **tensorial;
}typedef Parametros;

void *thread_quadrante(void *arg);

void calcular_tensorial_threads(Node *head);

#endif