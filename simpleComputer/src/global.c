#include "./../include/sc_register.h"
#include "./../include/sc_command.h"
#include "./../include/sc_memory.h"

int localRAM[sizeRAM];
short int sc_register;
int correctCommands[countCmd] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 
                               0x40, 0x41, 0x42, 0x43, 0x59};

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

