CC = gcc
CFLAGS = -g3 -std=c99
LIB = -lCPU -lTerm -lSimpleComputer -lAsm -lWrite -lReadInt -lBigChars -lReadKey  -L../lib

all: ./obj/main.o 
	$(CC) ./obj/main.o -o ./../bin/simplecomputer $(CFLAGS) $(LIB)


./obj/main.o: ./src/main.c
	$(CC) -c ./src/main.c -o ./obj/main.o $(CFLAGS) 

clean:
	rm -f ./obj/*.o

restruct:
	make clean
	make all


