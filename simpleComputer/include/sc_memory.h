/*
  Created by JIexa24 (Alexey R.)
*/
/*
 Operatioon with localMemory
*/
#ifndef SC_MEMORY_H
#define SC_MEMORY_H

#include "./sc.h"

/*initialization RAM in 0*/
int sc_memoryInit(void);

/*initialization addres by value*/
int sc_memorySet(int addres, int value);

/*return value on addres to value*/
int sc_memoryGet(int addres, int* value);

/*save RAM in binary to file*/
volatile int sc_memorySave(char* filename);

/*load RAM from file*/
volatile int sc_memoryLoad(char* filename);

#endif
