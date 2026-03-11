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

### O código foi implementado num sistema operacional LINUX