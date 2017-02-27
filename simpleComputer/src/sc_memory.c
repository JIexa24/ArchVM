/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/sc_memory.h"
#include "./../include/sc_register.h"

/*
  ERR_WRONG_ADDR -1
  ERR_OPEN_FILE -2
  ERR_FILE -3
  ERR_UNCORRECT_COMMAND -4
  ERR_ATTRIBUTE_BIT -5
  ERR_WRONG_FLAG -6

  int localRAM[sizRAM];
  short int sc_register;
  const int correctCommands[] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 
                               0x40, 0x41, 0x42, 0x43,0x52, 0x59};
  const int countCmd = 13;
*/

extern int localRAM[];
extern short int sc_register;

extern int correctCommands[];

int sc_memoryInit(void)
{
  for (int i = 0; i < sizeRAM; i++) {
    localRAM[i] = 0;
  }

  return 0;
}
/*---------------------------------------------------------------------------*/
int sc_memorySet(int addres, int value)
{
  if ((addres < sizeRAM) && (addres >= 0)) { 
    localRAM[addres] = value; 
    return 0;
  } else {
    sc_regSet(FLAG_OUTMEM, 1);
    return ERR_WRONG_ADDR;
  }
}
/*---------------------------------------------------------------------------*/
int sc_memoryGet(int addres, int* value)
{
  if ((addres < sizeRAM) && (addres >=0) && (value != NULL)) { 
    *value = localRAM[addres];
    return 0;
  } else {
    sc_regSet(FLAG_OUTMEM, 1);
    return ERR_WRONG_ADDR;
  }
}
/*---------------------------------------------------------------------------*/
int sc_memorySave(char* filename)
{
  FILE *data;
  int write;

  data = fopen(filename, "wb");

  if (data == NULL) {
    return ERR_OPEN_FILE;
  } else {
    write = fwrite(localRAM, sizeof(*localRAM) * sizeRAM, 1, data);
    fclose(data);
    if (write != 1)
      return ERR_FILE;
    else
      return 0;
  }
}
/*---------------------------------------------------------------------------*/
int sc_memoryLoad(char* filename)
{
  FILE *data;
  int read;
  int i;

  data = fopen(filename, "rb");
  if (data == NULL) {
    return ERR_OPEN_FILE;
  }
  read = fread(localRAM, sizeof(*localRAM) * sizeRAM, 1, data);
  for (i = 0; i < 100; i++) {
    localRAM[i] &= 0x7FFF;
  }
  fclose(data);
  if (read != 1) {
    return ERR_FILE;
  } else {
    return 0;
  }
}
