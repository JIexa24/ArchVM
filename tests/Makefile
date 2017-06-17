CC = gcc
CFLAGS = -g3 -std=c99
LIB = -lCPU -lTerm -lSimpleComputer -lAsm -lBasic -lWrite -lReadInt -lBigChars -lReadKey  -L../lib

all: ./bin/tests
	@echo " "
	@./bin/tests
	@echo " "

./bin/tests: ./obj/main.o ./obj/testsSC.o ./obj/testsAsm.o ./obj/testsBasic.o
	$(CC) ./obj/main.o ./obj/testsSC.o -o ./bin/tests ./obj/testsAsm.o ./obj/testsBasic.o $(LIB) $(CMAKELIB)

./obj/testsSC.o: ./src/testsSC.c
	$(CC) -c ./src/testsSC.c -o ./obj/testsSC.o $(CFLAGS)

./obj/testsAsm.o: ./src/testsAsm.c
	$(CC) -c ./src/testsAsm.c -o ./obj/testsAsm.o $(CFLAGS)

./obj/testsBasic.o: ./src/testsBasic.c
	$(CC) -c ./src/testsBasic.c -o ./obj/testsBasic.o $(CFLAGS)

./obj/main.o: ./src/main.c
	$(CC) -c ./src/main.c -o ./obj/main.o $(CFLAGS)

run:
	@./bin/tests

RUNTESTCMAKE:
	@echo " "
	@./bin/tests_ctest

restruct:
	rm ./obj/*.o
	make all
