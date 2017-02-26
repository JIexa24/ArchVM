CC = gcc
CFLAGS = -g
LIB = -lCPU -lTerm -lSimpleComputer -lWriteInt -lReadInt -lBigChars -lHardDrive -lReadKey  -lm -L../lib

all: ./obj/main.o 
	$(CC) ./obj/main.o -o ./../bin/simpleComputer $(CFLAGS) $(LIB)

./obj/main.o: ./src/main.c
	$(CC) -c ./src/main.c -o ./obj/main.o $(CFLAGS) 

clean:
	rm -f ./obj/*.o

restruct:
	make clean
	make all


