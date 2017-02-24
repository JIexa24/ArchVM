CC = gcc
CFLAGS = -g

all: ./obj/hardDrive.o 
	ar rvs ./../lib/libHardDrive.a ./obj/hardDrive.o

./obj/hardDrive.o: ./src/hardDrive.c
	$(CC) -c ./src/hardDrive.c -o ./obj/hardDrive.o $(CFLAGS)

clean:
	rm -f ./obj/*.o

restruct:
	make clean
	make all


