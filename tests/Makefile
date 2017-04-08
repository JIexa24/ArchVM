CC = gcc
CFLAGS = -g3 -std=c99
LIB = -L../lib -lSimpleComputer

all: tst
	./bin/tests

tst: ./obj/main.o ./obj/testsSC.o 
	$(CC) ./obj/main.o ./obj/testsSC.o -o ./bin/tests $(LIB)

./obj/testsSC.o: ./src/testsSC.c
	$(CC) -c ./src/testsSC.c -o ./obj/testsSC.o $(CFLAGS)

./obj/main.o: ./src/main.c
	$(CC) -c ./src/main.c -o ./obj/main.o $(CFLAGS)

    
