all: MAIN 

MAIN: PRINT SIMPLECOMPUTER READ TERM READKEY BIGCHAR HARDDRIVE CPU ASM 
	make -C main

PRINT: ./lib/libWriteInt.a
	make -C print

READ: ./lib/libReadInt.a
	make -C scan

SIMPLECOMPUTER: ./lib/libSimpleComputer.a
	make -C simpleComputer

TERM: ./lib/libTerm.a
	make -C consoleSC

READKEY: ./lib/libReadKey.a
	make -C readKey

BIGCHAR: ./lib/libBigChars.a
	make -C bc

HARDDRIVE: ./lib/libHardDrive.a
	make -C hardDrive

CPU: ./lib/libCPU.a
	make -C cpu

ASM: ./lib/libAsm.a
	make -C asm


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
