CC = gcc
CFLAGS = -g

all: ./obj/main.o ./obj/asm.o
	$(CC) ./obj/main.o ./obj/asm.o -o ../bin/sat -L../lib -lSimpleComputer -lReadInt -lm

./obj/main.o: ./src/main.c
	$(CC) -c ./src/main.c $(CFLAGS) -o ./obj/main.o

./obj/asm.o: ./src/asm.c
	$(CC) -c ./src/asm.c $(CFLAGS) -o ./obj/asm.o

clean:
	rm -f ./obj/*.o
	rm -f ../bin/sat

restruct:
	make clean
	make all;
