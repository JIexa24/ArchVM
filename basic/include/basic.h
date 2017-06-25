/*
  Created by JIexa24 (Alexey R.)
*/
#ifndef BASIC_H
#define BASIC_H

#include "./../../cpu/include/cpu.h"

enum keywords {
  KEYW_REM = 1,
  KEYW_INPUT = 2,
  KEYW_OUTPUT = 3,
  KEYW_GOTO = 4,
  KEYW_IF = 5,
  KEYW_LET = 6,
  KEYW_END = 7,
  KEYW_E = -1
};

typedef struct varBasic {
  char name[2];
  int cell;
  int variable;
} var;

int keywordCode(char* str);
int testArgvB(char* argv[]);
int testFile(char* filename);
int parsingLineB(char* str, int output );
int basicTrans(int argc, char *argv[]);

#endif
