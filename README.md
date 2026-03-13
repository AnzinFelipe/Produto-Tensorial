# Produto Tensorial V2

## Como compilar e executar
para compilar escreva: 
- _make clean_
- _make_

para executar:
- _./tensor [arquivo1.txt] [arquivo2.txt]... [arquivoN.txt]_

para testar:
- _make test_

## Descrição dos arquivos:
- main.c: estrutura principal do código com a leitura dos arquivos de texto passados como argumentos.

- matriz.h: define a struct de matrizes e suas funções.

- matriz.c: contêm as funções da biblioteca matriz.h. As funções de adicionar matrizes na lista encadeada, liberar a lista, calcular o produto tensorial de todas as matrizes, criar o arquivo de saída contendo o produto final e as funções para tratar os possíveis erros dos arquivos.

- threads.h: define as funções que calculam o produto tensorial com threads e sua struct de parâmetros.

- threads.c: contêm as funções da biblioteca threads.h. As funções de calcular o produto tensorial que possuem duas maneiras diferentes de utilizar os threads.

- openMP.h: define a função que calcula o produto tensorial utilizando OpenMP.

- openMP.c: contêm a função da biblioteca openMP.h. A função de calcular o produto tensorial utilizando OpenMP.

### O código foi implementado num sistema operacional LINUX