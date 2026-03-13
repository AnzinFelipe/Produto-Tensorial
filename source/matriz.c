#include "matriz.h"
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <omp.h>

void adicionar_matriz(Node **head, FILE *fp) {
    int i, j;
    float num;
    int N = contar_N(*head, fp);
    Node *novo = (Node *)malloc(sizeof(Node));
    if (novo != NULL) {
        novo->N = N;
        novo->matriz = (float **)malloc(novo->N * sizeof(float *));
        for (i = 0; i < novo->N; i++) {
            novo->matriz[i] = (float *)malloc(novo->N * sizeof(float)); 
        }
        rewind(fp);

        for (int i = 0; i < novo->N; i++) {
            for (int j = 0; j < novo->N; j++) {
                fscanf(fp, "%f", &num);
                novo->matriz[i][j] = num;
            }
        }

        novo->prox = NULL;
        if (*head == NULL) {
            *head = novo;
        } else {
            Node *aux = *head;
            while (aux->prox != NULL) {
                aux = aux->prox;
            }
            aux->prox = novo;
        }
    }
}

void liberar_matrizes(Node **head) {
    Node *aux = *head;
    while (*head != NULL) {
        aux = *head;
        *head = (*head)->prox;
        for (int i = 0; i < aux->N; i++) {
            free(aux->matriz[i]);
        }
        free(aux->matriz);
        free(aux);
    }
    *head = NULL;
}

int contar_N(Node *head, FILE *fp) {
    int cont = 0;
    float num;
    int quadrado;
    while (fscanf(fp, "%f", &num) != EOF) {
        cont++;
    }
    quadrado = (int)sqrt(cont);
    if (quadrado * quadrado == cont) {
        return quadrado;
    } else {
        printf("[ERRO] Uma das matrizes indicada não é quadrada\n");
        liberar_matrizes(&head);
        exit(1);
    }
}

void verificar_numeros(Node *head, FILE *fp) {
    char caracter;

    while ((caracter = fgetc(fp)) != EOF) {
        if (!isdigit(caracter) && caracter != '.' && caracter != ' ' && caracter != '\n') {
            printf("[ERRO] Uma das matrizes passadas não contém apenas números\n");
            liberar_matrizes(&head);
            exit(1);
        }
    }
    rewind(fp);
}

void calcular_tensorial(Node *head) {

    double tempo;
    double inicio = omp_get_wtime();

    int produto1 = 1;
    Node *aux = head;
    Node *tensoriais = NULL;
    head = head->prox;

    while (head != NULL) {
        int novo_N = aux->N * head->N;
        float **tensorial = (float **)malloc(novo_N * sizeof(float *));
        for (int i = 0; i < novo_N; i++) {
            tensorial[i] = (float *)malloc(novo_N * sizeof(float));
        }
        for (int i = 0; i < aux->N; i++) {
            for (int j = 0; j < aux->N; j++) {
                for (int k = 0; k < head->N; k++) {
                    for (int l = 0; l < head->N; l++) {
                        tensorial[k + head->N * i][l + head->N * j] = aux->matriz[i][j] * head->matriz[k][l];
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
        
        if (produto1 == 1) {
            aux = tensoriais;
            produto1 = 0;
        } else {
            aux = aux->prox;
        }

        for (int i = 0; i < novo_N; i++) {
            free(tensorial[i]);
        }
        free(tensorial);

        head = head->prox;
    }
    double fim = omp_get_wtime();
    tempo = fim - inicio;
    printf("Tempo de execução com a implementação serial: %.6f segundos\n", tempo);

    criar_resultado(tensoriais);
    liberar_matrizes(&tensoriais);
}

void criar_resultado(Node *head) {
    FILE *resultado = fopen("tensor_ifcvd.out", "w");

    if (resultado != NULL) {
        while (head->prox != NULL) {
            head = head->prox;
        }
        for (int i = 0; i < head->N; i++) {
            for (int j = 0; j < head->N; j++) {
                if (j == head->N - 1) {
                    if (i == head->N - 1) {
                        fprintf(resultado, "%.1f", head->matriz[i][j]);
                    } else {
                        fprintf(resultado, "%.1f\n", head->matriz[i][j]);
                    }
                } else {
                    fprintf(resultado, "%.1f ", head->matriz[i][j]);
                }
            }
        }
        fclose(resultado);
    } else {
        printf("[ERRO] Não foi possível criar o arquivo final\n");
    }
}

void printar_resultado(Node *head) {
    while (head->prox != NULL) {
        head = head->prox;
    }
    for (int i = 0; i < head->N; i++) {
        for (int j = 0; j < head->N; j++) {
            if (j == head->N - 1) {
                    printf("%.1f\n", head->matriz[i][j]);
            } else {
                printf("%.1f ", head->matriz[i][j]);
            }
        }
    }
}
