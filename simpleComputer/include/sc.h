#ifndef SC_H
#define SC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define sizeRAM 100 
 
#define FLAG_OVERFLOW 0    // overflow flag
#define FLAG_DIVISION 1
#define FLAG_OUTMEM 2      // out of memory
#define FLAG_INTERRUPT 3
#define FLAG_COMMAND 4     // wrong command

#define ERR_WRONG_ADDR -1
#define ERR_OPEN_FILE -2
#define ERR_FILE_SIZE -3
#define ERR_UNCORRECT_COMMAND -4
#define ERR_ATTRIBUTE_BIT -5
#define ERR_WRONG_FLAG -6

#define BITSET(A, B) (A =((A) | (1 << (B))))
#define BITCLEAR(A, B) (A = ((A) & ~(1 << (B))))
#define BITCHECK(A, B) (((A) >> B) & 1)

int localRAM[sizeRAM];
short int sc_register;

const int correctCommands[] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 
                               0x40, 0x41, 0x42, 0x43, 0x59};
const int countCmd = 13;

int intCompare(const void *a, const void *b)
{
  if (*(int*)a < *(int*)b) { 
    return -1;
  } else if (*(int*)a > *(int*)b) {
    return 1;
  } else {
    return 0;
  }
}

#endif
