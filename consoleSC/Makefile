CC = gcc
CFLAGS = -g

all: ./../lib/libTerm.a

./../lib/libTerm.a: ./obj/term.o
	ar rvs ./../lib/libTerm.a ./obj/term.o


./obj/term.o: ./src/term.c
	$(CC) -c ./src/term.c -o ./obj/term.o -lWriteInt -L../lib/ $(CFLAGS)

tst: ./tst/main.o
	$(CC) ./tst/main.o -lTerm -lWriteInt -L../lib/

./tst/main.o: ./tst/main.c
	$(CC) -c ./tst/main.c -o ./tst/main.o $(CFLAGS)

restruct:
	make clean
	make all

clean:
	rm -f obj/*.o
	rm -f tst/*.o
	rm -f a.out
