/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/sc_memory.h"
#include "./../include/sc_register.h"

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
  FILE *data = NULL;
  int write  = 0;

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
  FILE *data       = NULL;
  int read         = 0;
  int i            = 0;
  int ram[sizeRAM] = {0};

  data = fopen(filename, "rb");
  if (data == NULL) {
    return ERR_OPEN_FILE;
  }

  read = fread(ram, sizeof(*ram) * sizeRAM, 1, data);

  for (i = 0; i < sizeRAM; i++) {
    ram[i] &= 0x7FFF;
  }
  fclose(data);
  if (read != 1) {
    return ERR_FILE;
  } else {
    for (i = 0; i < sizeRAM; i++) {
      localRAM[i] = ram[i];
    }
    return 0;
  }
}
