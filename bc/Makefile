CC = gcc

all: ./obj/bc.o
	ar rvs ../lib/libBigChars.a ./obj/bc.o

./obj/bc.o: ./src/bc.c
	gcc -c ./src/bc.c -o ./obj/bc.o -g

clean:
	rm -f ./obj/*.o

tst: ./tst/main.o
	$(CC) ./tst/main.o -lBigChars -lTerm -lWriteInt -L../lib/

./tst/main.o: ./tst/main.c
	$(CC) -c ./tst/main.c -o ./tst/main.o
