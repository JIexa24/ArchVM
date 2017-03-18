all: PRINT SIMPLECOMPUTER READ TERM READKEY BIGCHAR HARDDRIVE CPU ASM MAIN 

PRINT:
	make restruct -C print

READ:
	make restruct -C scan

SIMPLECOMPUTER:
	make restruct -C simpleComputer

TERM:
	make restruct -C consoleSC

READKEY:
	make restruct -C readKey

BIGCHAR:
	make restruct -C bc

HARDDRIVE:
	make restruct -C hardDrive

CPU:
	make restruct -C cpu

ASM:
	make restruct -C asm

MAIN:
	make restruct -C main

restruct:
	make clean
	make all

clean:
	rm -f lib/*
	rm -f simpleComputer/obj/*.o
	rm -f simpleComputer/tst/*.o
	rm -f simpleComputer/a.out
	rm -f consoleSC/obj/*.o
	rm -f consoleSC/tst/*.o
	rm -f consoleSC/a.out
	rm -f readKey/obj/*.o
	rm -f readKey/tst/*.o
	rm -f readKey/a.out
	rm -f bc/obj/*.o
	rm -f bc/tst/*.o
	rm -f bc/a.out
	rm -f print/obj/*.o
	rm -f hardDrive/obj/*.o
	rm -f cpu/obj/*.o
	rm -f main/obj/*.o
