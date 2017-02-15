CC = gcc
CFLAGS = -g

all: ./obj/term.o tst
	ar rvs ./../lib/libTerm.a ./obj/term.o

./obj/term.o: ./src/term.c
	$(CC) -c ./src/term.c -o ./obj/term.o $(CFLAGS)

clean:
	rm -f ./obj/*.o

tst: ./tst/main.o
	$(CC) ./tst/main.o -lTerm -L../lib/

./tst/main.o: ./tst/main.c
	$(CC) -c ./tst/main.c -o ./tst/main.o $(CFLAGS)
