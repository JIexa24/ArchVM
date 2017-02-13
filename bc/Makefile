CC = gcc

all: ./obj/bc.o
	ar rvs ../lib/libbigChars.a ./obj/bc.o

./obj/bc.o: ./src/bc.c
	gcc -c ./src/bc.c -o ./obj/bc.o -g

clean:
	rm -f ./obj/*.o

tst: ./tst/main.o
	$(CC) ./tst/main.o -lbigChars -lTerm -L../lib/

./tst/main.o: ./tst/main.c
	$(CC) -c ./tst/main.c -o ./tst/main.o
