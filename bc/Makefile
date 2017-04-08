CC = gcc
CFLAGS = -g3 -std=c99

all: ./../lib/libBigChars.a

./../lib/libBigChars.a: ./obj/bc.o
	ar rvs ./../lib/libBigChars.a ./obj/bc.o

./obj/bc.o: ./src/bc.c
	gcc -c ./src/bc.c -o ./obj/bc.o $(CFLAGS)

restruct:
	make clean
	make all

clean:
	rm -f obj/*.o
