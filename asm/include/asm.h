/*
  Created by JIexa24 (Alexey R.)
*/
#ifndef ASM_H
#define ASM_H

#include "./../../cpu/include/cpu.h"

volatile int asmTrans(int argc, char** argv);
volatile int asmCommand(char *str);
volatile int parsingLine(char* str, int* addres, int* value);
int strToCommand(char* ptr,int* value);
int testArgv(char* argv[]);

#endif
