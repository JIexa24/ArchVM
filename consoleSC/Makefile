CC = gcc
CFLAGS = -g3 -std=c99

all: ./../lib/libTerm.a

./../lib/libTerm.a: ./obj/term.o
	ar rvs ./../lib/libTerm.a ./obj/term.o


./obj/term.o: ./src/term.c
	$(CC) -c ./src/term.c -o ./obj/term.o -lWriteInt -L../lib/ $(CFLAGS)

restruct:
	make clean
	make all

clean:
	rm -f obj/*.o
