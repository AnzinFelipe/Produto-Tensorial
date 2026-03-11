#include "matriz.h"
#include <unistd.h>
#include <pthread.h>

int i = 0;

void *thread_quadrante(void *arg) {
    printf("%d\n", i);
}

void calcular_tensorial_threads() {
    for (int j = 0; j < 2; j++) {
        i++;
        pthread_t tid, tid2;
    
        pthread_create(&tid, NULL, thread_quadrante, NULL);
        pthread_create(&tid2, NULL, thread_quadrante, NULL);

        pthread_join(tid, NULL);
        pthread_join(tid2, NULL);
        printf("Threads do loop acabaram\n");
    }
    printf("Saiu do loop\n");
}