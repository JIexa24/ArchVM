CC = gcc
CFLAGS = -g3 -std=c99

all: ./../lib/libSimpleComputer.a

./../lib/libSimpleComputer.a: ./obj/sc_memory.o ./obj/sc_command.o ./obj/sc_register.o ./obj/global.o
	ar rvs ./../lib/libSimpleComputer.a ./obj/sc_memory.o ./obj/sc_command.o ./obj/sc_register.o ./obj/global.o

./obj/sc_memory.o: ./src/sc_memory.c
	$(CC) -c ./src/sc_memory.c -o ./obj/sc_memory.o $(CFLAGS)

./obj/sc_command.o: ./src/sc_command.c
	$(CC) -c ./src/sc_command.c -o ./obj/sc_command.o $(CFLAGS)

./obj/sc_register.o: ./src/sc_register.c
	$(CC) -c ./src/sc_register.c -o ./obj/sc_register.o $(CFLAGS)

./obj/global.o: ./src/global.c
	$(CC) -c ./src/global.c -o ./obj/global.o $(CFLAGS)

restruct:
	make clean
	make all

clean:
	rm -f obj/*.o
