CC = gcc

all: ./obj/bc.o
	ar rvs ../lib/libbigChars.a ./obj/bc.o

./obj/bc.o: ./src/bc.c
	gcc -c ./src/bc.c -o ./obj/bc.o -g

clean:
	rm -f ./obj/*.o
