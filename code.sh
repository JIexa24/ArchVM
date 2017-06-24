#!/bin/bash
echo "--------Function main--------" > code.txt
echo "----------------main.c----------------" >> code.txt
cat ./main/src/main.c >> code.txt
echo "--------libSimpleComputer.a--------" >> code.txt
echo "----------------global.c----------------" >> code.txt
cat ./simpleComputer/src/global.c >> code.txt
echo "----------------sc_memory.c----------------" >> code.txt
cat ./simpleComputer/src/sc_memory.c >> code.txt
echo "----------------print.c----------------" >> code.txt
cat ./simpleComputer/src/sc_register.c >> code.txt
echo "----------------handlers.c----------------" >> code.txt
cat ./simpleComputer/src/sc_command.c >> code.txt
echo "----------------sc.h----------------" >> code.txt
cat ./simpleComputer/include/sc.h >> code.txt
echo "----------------sc_memory.h----------------" >> code.txt
cat ./simpleComputer/include/sc_memory.h >> code.txt
echo "----------------sc_register.h----------------" >> code.txt
cat ./simpleComputer/include/sc_register.h >> code.txt
echo "----------------sc_command.h----------------" >> code.txt
cat ./simpleComputer/include/sc_command.h >> code.txt

echo "--------libTerm.a--------" >> code.txt
echo "----------------term.c----------------" >> code.txt
cat ./consoleSC/src/term.c >> code.txt
echo "----------------term.h----------------" >> code.txt
cat ./consoleSC/include/term.h >> code.txt

echo "--------libBigChars.a--------" >> code.txt
echo "----------------bc.c----------------" >> code.txt
cat ./bc/src/bc.c >> code.txt
echo "----------------bc.h----------------" >> code.txt
cat ./bc/include/bc.h >> code.txt

echo "--------libReadKey.a--------" >> code.txt
echo "----------------readkey.c----------------" >> code.txt
cat ./readKey/src/readkey.c >> code.txt
echo "----------------readkey.h----------------" >> code.txt
cat ./readKey/include/readkey.h >> code.txt

echo "--------libCPU.a--------" >> code.txt
echo "----------------cpu.c----------------" >> code.txt
cat ./cpu/src/cpu.c >> code.txt
echo "----------------print.c----------------" >> code.txt
cat ./cpu/src/print.c >> code.txt
echo "----------------handlers.c----------------" >> code.txt
cat ./cpu/src/handlers.c >> code.txt
echo "----------------command.c----------------" >> code.txt
cat ./cpu/src/command.c >> code.txt
echo "----------------change.c----------------" >> code.txt
cat ./cpu/src/change.c >> code.txt
echo "----------------read.c----------------" >> code.txt
cat ./cpu/src/read.c >> code.txt
echo "----------------cpu.h----------------" >> code.txt
cat ./cpu/include/cpu.h >> code.txt

echo "--------libAsm.a--------" >> code.txt
echo "----------------asm.c----------------" >> code.txt
cat ./asm/src/asm.c >> code.txt
echo "----------------main.c----------------">> code.txt
cat ./asm/src/main.c >> code.txt
echo "----------------asm.h----------------">> code.txt
cat ./asm/include/asm.h >> code.txt

echo "--------libBasic.a--------" >> code.txt
echo "----------------basic.c----------------" >> code.txt
cat ./basic/src/basic.c >> code.txt
echo "----------------main.c----------------">> code.txt
cat ./basic/src/main.c >> code.txt
echo "----------------basic.h----------------">> code.txt
cat ./basic/include/basic.h >> code.txt

echo "--------libReadInt.a--------" >> code.txt
echo "----------------readInt.c----------------" >> code.txt
cat ./scan/src/readInt.c >> code.txt
echo "----------------readInt.h----------------" >> code.txt
cat ./scan/include/readInt.h >> code.txt

echo "--------libWrite.a--------" >> code.txt
echo "----------------write.c----------------" >> code.txt
cat ./print/src/write.c >> code.txt
echo "----------------write.h----------------" >> code.txt
cat ./print/include/write.h >> code.txt
