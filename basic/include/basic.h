#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  char name;
  int operand;
} var;

int keywordCode(char *str);
int testArgv(char *argv[]);

#endif
