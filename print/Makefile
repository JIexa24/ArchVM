CC = gcc
CFLAGS = -g3 -std=c99

all: ./../lib/libWrite.a

./../lib/libWrite.a: ./obj/write.o 
	ar rvs ./../lib/libWrite.a ./obj/write.o

./obj/write.o: ./src/write.c
	$(CC) -c ./src/write.c -o ./obj/write.o $(CFLAGS)

clean:
	rm -f ./obj/*.o

restruct:
	make clean
	make all


