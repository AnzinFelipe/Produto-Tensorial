pasta_o = objects

pasta_s = source

tensor: main.o matriz.o
	gcc $(pasta_o)/main.o $(pasta_o)/matriz.o -o tensor -lm

main.o: pasta $(pasta_s)/main.c $(pasta_s)/matriz.h
	gcc -c $(pasta_s)/main.c -o $(pasta_o)/main.o

matriz.o: pasta $(pasta_s)/matriz.c $(pasta_s)/matriz.h
	gcc -c $(pasta_s)/matriz.c -o $(pasta_o)/matriz.o

pasta:
	mkdir -p $(pasta_o)

test: tensor
	./tensor matriz_test1.txt matriz_test2.txt

clean:
	rm -rf *$(pasta_o).o $(pasta_o) tensor