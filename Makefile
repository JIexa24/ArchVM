all:
	make -C build
	make TEST

HANDMADE:
	make -C print
	make -C scan
	make -C simpleComputer
	make -C consoleSC
	make -C readKey
	make -C bc
	make -C hardDrive
	make -C cpu
	make -C asm
	make -C main
	make TEST

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

TEST:
	make -C tests


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
