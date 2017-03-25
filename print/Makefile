CC = gcc
CFLAGS = -g3 -std=c99

all: ./../lib/libWriteInt.a

./../lib/libWriteInt.a: ./obj/writeInt.o 
	ar rvs ./../lib/libWriteInt.a ./obj/writeInt.o

./obj/writeInt.o: ./src/writeInt.c
	$(CC) -c ./src/writeInt.c -o ./obj/writeInt.o $(CFLAGS)

clean:
	rm -f ./obj/*.o

restruct:
	make clean
	make all


