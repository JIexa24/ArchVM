CC = gcc
CFLAGS = -g3 -std=c99
LIB = -L../../lib -lSimpleComputer

all: tst
	./bin/tests

tst: ./obj/main.o ./obj/tests.o 
	$(CC) ./obj/main.o ./obj/tests.o -o ./bin/tests $(LIB)

./obj/tests.o: ./src/tests.c
	$(CC) -c ./src/tests.c -o ./obj/tests.o $(CFLAGS)

./obj/main.o: ./src/tests.c
	$(CC) -c ./src/main.c -o ./obj/main.o $(CFLAGS)

    
