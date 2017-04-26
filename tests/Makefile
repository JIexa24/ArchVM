CC = gcc
CFLAGS = -g3 -std=c99
LIB = -L../lib -lSimpleComputer -lWriteInt
CMAKELIB = -L../build/simpleComputer -L../build/print

all: tst
	./bin/tests

tst: ./obj/main.o ./obj/testsSC.o
	$(CC) ./obj/main.o ./obj/testsSC.o -o ./bin/tests $(LIB) $(CMAKELIB)

./obj/testsSC.o: ./src/testsSC.c
	$(CC) -c ./src/testsSC.c -o ./obj/testsSC.o $(CFLAGS)

./obj/main.o: ./src/main.c
	$(CC) -c ./src/main.c -o ./obj/main.o $(CFLAGS)

