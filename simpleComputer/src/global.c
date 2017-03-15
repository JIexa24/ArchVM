/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/sc_register.h"
#include "./../include/sc_command.h"
#include "./../include/sc_memory.h"

int localRAM[sizeRAM];
short int sc_register;
int correctCommands[countCmd] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 
                                 0x40, 0x41, 0x42, 0x43, 0x51, 0x52, 0x53, 0x54,
                                 0x55, 0x56, 0x57, 0x58, 0x59, 0x60, 0x61, 0x61,
                                 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
                                 0x70, 0x71, 0x72, 0x73, 0x75, 0x76,};

int intCompare(const int *a, const int *b)
{
  if (*((int*)a) < *((int*)b)) { 
    return -1;
  } else if (*((int*)a) > *((int*)b)) {
    return 1;
  } else {
    return 0;
  }
}

