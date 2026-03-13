#include "matriz.h"
#include <stdlib.h>
#include <omp.h>

void calcular_tensorial_openmp(Node *head) {

    double tempo;
    double inicio = omp_get_wtime();
    omp_set_num_threads(8);

    Node *aux = head;
    Node *tensoriais = NULL;
    head = head->prox;

    while (head != NULL) {
        int novo_N = aux->N * head->N;
        float **tensorial = (float **)malloc(novo_N * sizeof(float *));
        for (int i = 0; i < novo_N; i++) {
            tensorial[i] = (float *)malloc(novo_N * sizeof(float));
        }


        #pragma omp parallel for collapse(2) schedule(static)
        for (int i = 0; i < aux->N; i++) {
            for (int j = 0; j < aux->N; j++) {
                float num_matriz1 = aux->matriz[i][j];
                for (int k = 0; k < head->N; k++) {
                    for (int l = 0; l < head->N; l++) {
                        tensorial[k + head->N * i][l + head->N * j] = num_matriz1 * head->matriz[k][l];
                    }
                }
            }
        }

        Node *novo = (Node *)malloc(sizeof(Node));
        novo->N = novo_N;
        novo->prox = NULL;
        novo->matriz = (float **)malloc(novo->N * sizeof(float *));
        for (int i = 0; i < novo->N; i++) {
            novo->matriz[i] = (float *)malloc(novo->N * sizeof(float)); 
        }
        for (int i = 0; i < novo->N; i++) {
            for (int j = 0; j < novo->N ; j++) {
                novo->matriz[i][j] = tensorial[i][j];
            }
        }
        if (tensoriais == NULL) {
            tensoriais = novo;
        } else {
            Node *t_aux = tensoriais;
            while (t_aux->prox != NULL) {
                t_aux = t_aux->prox;
            }
            t_aux ->prox = novo;
        }
        
        aux = novo;

        for (int i = 0; i < novo_N; i++) {
            free(tensorial[i]);
        }
        free(tensorial);

        head = head->prox;
    }
    double fim = omp_get_wtime();
    tempo = fim - inicio;
    printf("Tempo de execução com a implementação usando OpenMP: %.6f segundos\n", tempo);

    liberar_matrizes(&tensoriais);
}