#ifndef SC_H
#define SC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define sizeRAM 100 
#define countCmd 13 
 
#define FLAG_OVERFLOW 0    // overflow flag
#define FLAG_DIVISION 1    // ZERO
#define FLAG_OUTMEM 2      // out of memory
#define FLAG_INTERRUPT 3   // interrupt (ISIG)
#define FLAG_COMMAND 4     // wrong command
#define FLAG_ODD 5         // 
//#define FLAG_CANON 6       // data from queue input
#define FLAG_ECHO 6        // print simb drom stdin

#define ERR_WRONG_ADDR -1
#define ERR_OPEN_FILE -2
#define ERR_FILE -3
#define ERR_UNCORRECT_COMMAND -4
#define ERR_ATTRIBUTE_BIT -5
#define ERR_WRONG_FLAG -6

#define BITSET(A, B) (A =((A) | (1 << (B))))
#define BITCLEAR(A, B) (A = ((A) & ~(1 << (B))))
#define BITCHECK(A, B) (((A) >> B) & 1)

int intCompare(const int *a, const int *b);

#endif
