CC = gcc
CFLAGS = -g

all: ./obj/readkey.o 
	ar rvs ./../lib/libreadKey.a ./obj/readkey.o

./obj/readkey.o: ./src/readkey.c
	$(CC) -c ./src/readkey.c -o ./obj/readkey.o $(CFLAGS)

clean:
	rm -f ./obj/*.o
	rm -f a.out
	rm -f ./tst/main.o
	rm -f termsettings

tst: ./tst/main.o
	$(CC) ./tst/main.o -lreadKey -L../lib/

./tst/main.o: ./tst/main.c
	$(CC) -c ./tst/main.c -o ./tst/main.o $(CFLAGS)
