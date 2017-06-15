CC = gcc
CFLAGS = -g3 -std=c99
LIB = -L../lib -lSimpleComputer -lWrite -lAsm -lReadInt
CMAKELIB = -L../build/simpleComputer -L../build/print -L../build/asm -L../build/scan

all: ./bin/tests
	./bin/tests

./bin/tests: ./obj/main.o ./obj/testsSC.o ./obj/testsAsm.o
	$(CC) ./obj/main.o ./obj/testsSC.o -o ./bin/tests ./obj/testsAsm.o $(LIB) $(CMAKELIB)

./obj/testsSC.o: ./src/testsSC.c
	$(CC) -c ./src/testsSC.c -o ./obj/testsSC.o $(CFLAGS)

./obj/testsAsm.o: ./src/testsAsm.c
	$(CC) -c ./src/testsAsm.c -o ./obj/testsAsm.o $(CFLAGS)

./obj/main.o: ./src/main.c
	$(CC) -c ./src/main.c -o ./obj/main.o $(CFLAGS)

restruct:
	rm ./obj/*.o
	make all
