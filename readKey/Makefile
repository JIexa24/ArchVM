CC = gcc
CFLAGS = -g

all: ./obj/readkey.o tst
	ar rvs ./../lib/libReadKey.a ./obj/readkey.o

./obj/readkey.o: ./src/readkey.c
	$(CC) -c ./src/readkey.c -o ./obj/readkey.o $(CFLAGS)

clean:
	rm -f ./obj/*.o

tst: ./tst/main.o
	$(CC) ./tst/main.o -lReadKey -L../lib/

./tst/main.o: ./tst/main.c
	$(CC) -c ./tst/main.c -o ./tst/main.o $(CFLAGS)
