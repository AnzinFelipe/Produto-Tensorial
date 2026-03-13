pasta_o = objects

pasta_s = source

FLAGS = -pthread -fopenmp

tensor: main.o matriz.o threads.o
	gcc $(FLAGS) $(pasta_o)/main.o $(pasta_o)/matriz.o $(pasta_o)/threads.o -o tensor -lm

main.o: pasta $(pasta_s)/main.c $(pasta_s)/matriz.h
	gcc -c $(pasta_s)/main.c -o $(pasta_o)/main.o

threads.o: pasta $(pasta_s)/threads.c $(pasta_s)/threads.h $(pasta_s)/matriz.h
	gcc -c $(pasta_s)/threads.c -o $(pasta_o)/threads.o

matriz.o: pasta $(pasta_s)/matriz.c $(pasta_s)/matriz.h
	gcc -c $(pasta_s)/matriz.c -o $(pasta_o)/matriz.o

pasta:
	mkdir -p $(pasta_o)

test: tensor
	./tensor matriz_test1.txt matriz_test2.txt matriz_test3.txt

clean:
	rm -rf *$(pasta_o).o $(pasta_o) tensor