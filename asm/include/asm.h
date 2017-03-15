/*
  Created by JIexa24 (Alexey R.)
*/
#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <string.h>

#include "./../../simpleComputer/include/sc_register.h"
#include "./../../simpleComputer/include/sc_command.h"
#include "./../../simpleComputer/include/sc_memory.h"
#include "./../../scan/include/readInt.h"

int asmCommand(char *str);
int parsingLine(char* str, int* addres, int* value);
int strToCommand(char* ptr,int* value);
int testArgv(char* argv[]);
#endif
