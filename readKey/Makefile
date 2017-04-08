CC = gcc
CFLAGS = -g3 -std=c99

all: ./../lib/libReadKey.a

./../lib/libReadKey.a: ./obj/readkey.o 
	ar rvs ./../lib/libReadKey.a ./obj/readkey.o

./obj/readkey.o: ./src/readkey.c
	$(CC) -c ./src/readkey.c -o ./obj/readkey.o $(CFLAGS)

restruct:
	make clean
	make all

clean:
	rm -f obj/*.o
