#ifndef MATRIZ
#define MATRIZ

#include <stdio.h>

typedef struct Node {
    int N;
    float **matriz;
    struct Node *prox;
} Node;

void adicionar_matriz(Node **head, FILE *fp);

void liberar_matrizes(Node **head);

int contar_N(Node *head, FILE *fp);

void verificar_numeros(Node *head, FILE *fp);

void calcular_tensorial(Node *head);

void criar_resultado(Node *head);

void printar_resultado(Node *head);

#endif