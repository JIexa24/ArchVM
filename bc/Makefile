CC = gcc
CFLAGS = -g3 -std=c99

all: ./../lib/libBigChars.a

./../lib/libBigChars.a: ./obj/bc.o
	ar rvs ./../lib/libBigChars.a ./obj/bc.o

./obj/bc.o: ./src/bc.c
	gcc -c ./src/bc.c -o ./obj/bc.o $(CFLAGS)

tst: ./tst/main.o
	$(CC) ./tst/main.o -lBigChars -lTerm -lWriteInt -L../lib/

./tst/main.o: ./tst/main.c
	$(CC) -c ./tst/main.c -o ./tst/main.o $(CFLAGS)

restruct:
	make clean
	make all

clean:
	rm -f obj/*.o
	rm -f tst/*.o
	rm -f a.out
	rm -f bigtest
	rm -f bigchars
