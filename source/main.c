#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "threads.h"

int main( int argc, char *argv[]) {
    int cont;
    Node *matrizes = NULL;

    if (argc < 3) {
        printf("[ERRO] É preciso passar pelo menos 2 arquivos de texto contando matrizes como argumento\n");
        exit(1);
    }

    for (cont = 1; cont < argc; cont++) {

        FILE *fp = fopen(argv[cont], "r");
    
        if (fp != NULL) {
            verificar_numeros(matrizes, fp);
            adicionar_matriz(&matrizes, fp);
        } else {
            printf("[ERRO] Arquivo não encontrado\n");
            liberar_matrizes(&matrizes);
            exit(1);
        }

        fclose(fp);
    }

    calcular_tensorial_threads(matrizes);
    calcular_tensorial(matrizes);
    liberar_matrizes(&matrizes);

    return 0;
}
