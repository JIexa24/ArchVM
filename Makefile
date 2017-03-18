all: PRINT SIMPLECOMPUTER READ TERM READKEY BIGCHAR HARDDRIVE CPU ASM MAIN 

PRINT:
	make -C print

READ:
	make -C scan

SIMPLECOMPUTER:
	make -C simpleComputer

TERM:
	make -C consoleSC

READKEY:
	make -C readKey

BIGCHAR:
	make -C bc

HARDDRIVE:
	make -C hardDrive

CPU:
	make -C cpu

ASM:
	make -C asm

MAIN:
	make -C main

restruct:
	make clean
	make restruct -C print
	make restruct -C scan
	make restruct -C simpleComputer
	make restruct -C consoleSC
	make restruct -C readKey
	make restruct -C bc
	make restruct -C hardDrive
	make restruct -C cpu
	make restruct -C asm
	make restruct -C main

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
	rm -f asm/obj/*.o
