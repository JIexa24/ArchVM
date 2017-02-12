#ifndef SC_H
#define SC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define sizeRAM 100 
#define countCmd 13 
 
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

int intCompare(const int *a, const int *b);

#endif
