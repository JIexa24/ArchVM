CC = gcc
CFLAGS = -g3

all:  ./../bin/sbt

./../bin/sbt: ./obj/main.o  ./../lib/libBasic.a
	$(CC) ./obj/main.o -o ./../bin/sbt -lBasic -lAsm -lSimpleComputer -lReadInt -lm -L../lib

./../lib/libBasic.a: ./obj/basic.o
	ar rvs ./../lib/libBasic.a ./obj/basic.o

./obj/basic.o: ./src/basic.c
	$(CC) -c ./src/basic.c -o ./obj/basic.o $(CFLAGS)

./obj/main.o: ./src/main.c
	$(CC) -c ./src/main.c -o ./obj/main.o $(CFLAGS)

restruct:
	make clean
	make all

clean:
	rm -f obj/*.o
	rm -f ../bin/sat
