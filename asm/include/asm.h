/*
  Created by JIexa24 (Alexey R.)
*/
#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <string.h>

#include "./../../cpu/include/cpu.h"

#define TOKENSYMB ' '

int asmCommand(char *str);
int parsingLine(char* str, int* addres, int* value);
int strToCommand(char* ptr,int* value);
int testArgv(char* argv[]);
#endif
