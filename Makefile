all: PRINT SIMPLECOMPUTER TERM READKEY BIGCHAR

PRINT:
	make restruct -C print

SIMPLECOMPUTER:
	make restruct -C simpleComputer

TERM:
	make restruct -C consoleSC

READKEY:
	make restruct -C readKey

BIGCHAR:
	make restruct -C bc

restruct:
	make clean
	make all

clean:
	rm -f lib/*
	rm -f simpleComputer/obj/*.o
	rm -f simpleComputer/tst/*.o
	rm -f consoleSC/obj/*.o
	rm -f consoleSC/tst/*.o
	rm -f readKey/obj/*.o
	rm -f readKey/tst/*.o
	rm -f bc/obj/*.o
	rm -f bc/tst/*.o
