CC = gcc
CFLAGS = -g

all: ./obj/term.o 
	ar rvs ./../lib/libTerm.a ./obj/term.o

./obj/term.o: ./src/term.c
	$(CC) -c ./src/term.c -o ./obj/term.o $(CFLAGS)

clean:
	rm -f ./obj/*.o

