CC = gcc
CFLAGS = -g

all: ./../lib/libReadKey.a

./../lib/libReadKey.a: ./obj/readkey.o 
	ar rvs ./../lib/libReadKey.a ./obj/readkey.o

./obj/readkey.o: ./src/readkey.c
	$(CC) -c ./src/readkey.c -o ./obj/readkey.o $(CFLAGS)

tst: ./tst/main.o
	$(CC) ./tst/main.o -lReadKey -lWriteInt -L../lib/

./tst/main.o: ./tst/main.c
	$(CC) -c ./tst/main.c -o ./tst/main.o $(CFLAGS)

restruct:
	make clean
	make all

clean:
	rm -f obj/*.o
	rm -f tst/*.o
	rm -f a.out
	rm -f termsettings
