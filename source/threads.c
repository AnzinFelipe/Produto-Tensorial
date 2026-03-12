#include "threads.h"
#include "matriz.h"
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

Node *tensorais = NULL;

void *thread_quadrante(void *arg) {
    Parametros *p = (Parametros *)arg;
    int N = p->matriz2_N;
    int i = p->matriz1_i, j = p->matriz1_j;

    for (int k = 0; k < N; k++) {
        for (int l = 0; l < N; l++) {
            p->tensorial[k + N * i][l + N * j] = p->matriz1_num * p->matriz2[k][l];
        }
    }
    return NULL;
}

void calcular_tensorial_threads(Node *head) {
    
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

        pthread_t tids[aux->N * aux->N];
        Parametros *parametros = (Parametros *)malloc(aux->N * aux->N * sizeof(Parametros));

        for (int i = 0; i < aux->N; i++) {
            for (int j = 0; j < aux->N; j++) {
                int N = i * aux->N + j;
                parametros[N].matriz2 = head->matriz;
                parametros[N].tensorial = tensorial;
                parametros[N].matriz1_num = aux->matriz[i][j];
                parametros[N].matriz2_N = head->N;
                parametros[N].matriz1_i = i;
                parametros[N].matriz1_j = j;
                pthread_create(&tids[N], NULL, thread_quadrante, &parametros[N]);
            }
        }

        for (int i = 0; i < aux->N; i++) {
            for (int j = 0; j < aux->N; j++) {
                pthread_join(tids[i * aux->N + j], NULL);
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
        free(parametros);

        head = head->prox;
    }
    printar_resultado(tensoriais);
    liberar_matrizes(&tensoriais);
}