CC = gcc
CFLAGS = -g3

all:  ./../lib/libAsm.a ./../bin/sat

./../bin/sat: ./obj/main.o ./obj/asm.o
	$(CC) ./obj/main.o ./obj/asm.o -o ./../bin/sat -lSimpleComputer -lReadInt -lm -L../lib

./../lib/libAsm.a: ./obj/asm.o
	ar rvs ./../lib/libAsm.a ./obj/asm.o 

./obj/asm.o: ./src/asm.c
	$(CC) -c ./src/asm.c -o ./obj/asm.o $(CFLAGS)

./obj/main.o: ./src/main.c
	$(CC) -c ./src/main.c -o ./obj/main.o $(CFLAGS)

restruct:
	make clean
	make all

clean:
	rm -f obj/*.o
	rm -f ../bin/sat
