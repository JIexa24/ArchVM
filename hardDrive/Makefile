CC = gcc
CFLAGS = -g3 -std=c99

all:  ./../bin/hard

./../bin/hard: ./obj/main.o ./../lib/libHardDrive.a 
	$(CC) ./obj/main.o -o ./../bin/hard -lHardDrive -lWriteInt -lReadInt -L../lib

./../lib/libHardDrive.a: ./obj/hardDrive.o ./obj/functions.o
	ar rvs ./../lib/libHardDrive.a ./obj/hardDrive.o ./obj/functions.o

./obj/functions.o: ./src/functions.c
	$(CC) -c ./src/functions.c -o ./obj/functions.o $(CFLAGS)

./obj/hardDrive.o: ./src/hardDrive.c
	$(CC) -c ./src/hardDrive.c -o ./obj/hardDrive.o $(CFLAGS)

./obj/main.o: ./src/main.c
	$(CC) -c ./src/main.c -o ./obj/main.o $(CFLAGS)

clean:
	rm -f ./obj/*.o

restruct:
	make clean
	make all


