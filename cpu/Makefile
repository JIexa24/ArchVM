CC = gcc
CFLAGS = -g
LIB = -L../lib -lTerm -lSimpleComputer -lWriteInt -lBigChars -lHardDrive -lReadKey 

all: ./obj/cpu.o ./obj/change.o ./obj/print.o ./obj/timer.o ./obj/global.o
	ar rvs ./../lib/libCPU.a ./obj/cpu.o ./obj/change.o ./obj/print.o ./obj/timer.o ./obj/global.o

./obj/cpu.o: ./src/cpu.c
	$(CC) -c ./src/cpu.c -o ./obj/cpu.o $(CFLAGS)  $(LIB)

./obj/change.o: ./src/change.c
	$(CC) -c ./src/change.c -o ./obj/change.o $(CFLAGS) $(LIB)

./obj/print.o: ./src/print.c
	$(CC) -c ./src/print.c -o ./obj/print.o $(CFLAGS) $(LIB)

./obj/timer.o: ./src/timer.c
	$(CC) -c ./src/timer.c -o ./obj/timer.o $(CFLAGS) $(LIB)

./obj/global.o: ./src/global.c
	$(CC) -c ./src/global.c -o ./obj/global.o $(CFLAGS)  $(LIB)

clean:
	rm -f ./obj/*.o

restruct:
	make clean
	make all


