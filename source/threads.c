#include "threads.h"
#include "matriz.h"
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <omp.h>

Node *tensorais = NULL;

void *thread_por_linha(void *arg) {
    Parametros *p = (Parametros *)arg;
    int N2 = p->matriz2_N;
    int N1 = p->matriz1_N;
    int i = p->matriz1_i;

    for (int j = 0; j < N1; j++) {
        for (int k = 0; k < N2; k++) {
            for (int l = 0; l < N2; l++) {
                p->tensorial[k + N2 * i][l + N2 * j] = p->matriz1[i][j] * p->matriz2[k][l];
            }
        }
    }
    return NULL;
}

void calcular_tensorial_threads(Node *head) {
    
    double tempo;
    double inicio = omp_get_wtime();

    int produto1 = 1;
    Node *aux = head;
    head = head->prox;
    Node *tensoriais = NULL;

    while (head != NULL) {
        int novo_N = aux->N * head->N;
        float **tensorial = (float **)malloc(novo_N * sizeof(float *));
        for (int i = 0; i < novo_N; i++) {
            tensorial[i] = (float *)malloc(novo_N * sizeof(float));
        }

        pthread_t tids[aux->N];
        Parametros *parametros = (Parametros *)malloc(aux->N * sizeof(Parametros));

        for (int i = 0; i < aux->N; i++) {
            parametros[i].matriz2 = head->matriz;
            parametros[i].tensorial = tensorial;
            parametros[i].matriz1 = aux->matriz;
            parametros[i].matriz1_N = aux->N;
            parametros[i].matriz2_N = head->N;
            parametros[i].matriz1_i = i;
            pthread_create(&tids[i], NULL, thread_por_linha, &parametros[i]);
        }

        for (int i = 0; i < aux->N; i++) {
            pthread_join(tids[i], NULL);
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
        free(parametros);

        head = head->prox;
    }

    double fim = omp_get_wtime();
    tempo = fim - inicio;
    printf("Tempo de execução com a primeira implementação usando Pthreads: %.6f segundos\n", tempo);

    //printar_resultado(tensoriais);
    liberar_matrizes(&tensoriais);
}