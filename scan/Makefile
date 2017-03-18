CC = gcc
CFLAGS = -g

all: ./../lib/libReadInt.a

./../lib/libReadInt.a: ./obj/readInt.o 
	ar rvs ./../lib/libReadInt.a ./obj/readInt.o 

./obj/readInt.o: ./src/readInt.c
	$(CC) -c ./src/readInt.c -o ./obj/readInt.o $(CFLAGS)

clean:
	rm -f ./obj/*.o

restruct:
	make clean
	make all


