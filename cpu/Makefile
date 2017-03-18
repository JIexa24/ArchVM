CC = gcc
CFLAGS = -g

all: ./obj/cpu.o ./obj/change.o ./obj/print.o ./obj/timer.o ./obj/global.o ./obj/read.o ./obj/command.o
	ar rvs ./../lib/libCPU.a ./obj/cpu.o ./obj/change.o ./obj/print.o ./obj/timer.o ./obj/global.o ./obj/read.o ./obj/command.o

./obj/cpu.o: ./src/cpu.c
	$(CC) -c ./src/cpu.c -o ./obj/cpu.o $(CFLAGS) 

./obj/change.o: ./src/change.c
	$(CC) -c ./src/change.c -o ./obj/change.o $(CFLAGS)

./obj/print.o: ./src/print.c
	$(CC) -c ./src/print.c -o ./obj/print.o $(CFLAGS) 

./obj/read.o: ./src/read.c
	$(CC) -c ./src/read.c -o ./obj/read.o $(CFLAGS)

./obj/timer.o: ./src/timer.c
	$(CC) -c ./src/timer.c -o ./obj/timer.o $(CFLAGS)

./obj/global.o: ./src/global.c
	$(CC) -c ./src/global.c -o ./obj/global.o $(CFLAGS)

./obj/command.o: ./src/command.c
	$(CC) -c ./src/command.c -o ./obj/command.o $(CFLAGS)

clean:
	rm -f ./obj/*.o

restruct:
	make clean
	make all


