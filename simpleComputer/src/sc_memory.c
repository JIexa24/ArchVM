/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/sc_memory.h"
#include "./../include/sc_register.h"

extern int localRAM[];

int sc_memoryInit(void)
{
  int i;
  for (i = 0; i < sizeRAM; i++) {
    localRAM[i] = 0;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
int sc_memorySet(int addres, int value)
{
  if ((addres < sizeRAM) & (addres >= 0)) {
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
  if ((addres < sizeRAM) & (addres >=0) & (value != NULL)) {
    *value = localRAM[addres];
    return 0;
  } else {
    sc_regSet(FLAG_OUTMEM, 1);
    return ERR_WRONG_ADDR;
  }
}
/*---------------------------------------------------------------------------*/
volatile int sc_memorySave(char* filename)
{
  int data        = 0;
  int writecount  = 0;

  if ((data = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
    return ERR_OPEN_FILE;
  }

  writecount = write(data, localRAM, sizeof(int) * sizeRAM);
  close(data);

  if (writecount != sizeof(int) * sizeRAM) {
    return ERR_FILE;
  } else {
    return 0;
  }
}
/*---------------------------------------------------------------------------*/
volatile int sc_memoryLoad(char* filename)
{
  int data         = 0;
  int readcount    = 0;
  int i            = 0;
  int ram[sizeRAM] = {0};

  if ((data = open(filename, O_RDONLY)) == -1) {
    return ERR_OPEN_FILE;
  }

  readcount = read(data, ram, sizeof(int) * sizeRAM);
  close(data);
  for (i = 0; i < sizeRAM; i++) {
    ram[i] &= 0x7FFF;
  }
  if (readcount != sizeof(int) * sizeRAM) {
    return ERR_FILE;
  } else {
    for (i = 0; i < sizeRAM; i++) {
      localRAM[i] = ram[i];
    }
    return 0;
  }
}
