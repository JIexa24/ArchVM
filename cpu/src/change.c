/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/cpu.h"

extern int accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern short int sc_register;

void setSignals()
{
  signal(SIGALRM, timerHand);
  signal(SIGUSR1, timerUrsignalHand);
}
/*---------------------------------------------------------------------------*/
int changeCell(int pos)
{
  int plusFlag, num;
  int command, operand, mem;
  refreshGui(pos);
  mt_gotoXY(1, 23);
  writeChar(1, "Enter num:");
  mt_gotoXY(1, 24);
  if (scanNum(&plusFlag, &num) != 0) {
    writeChar(2, "Not a number!");
    return -1;
  }
  if ((num >= 0) && (num < 0x8000)) {
    if (plusFlag) {
      command = (num >> 8) & 0x7F;
      if (num & 0x80) {
        writeChar(2, "Operand is 7 bit wide ( <= 7F). ");
        return -1;
      }
      operand = num & 0x7F;
      sc_commandEncode(command, operand, &mem);
    } else {
      mem = num | 0x4000;
    }
               
    if ((pos >= 0) && (pos < sizeRAM)) {
      sc_memorySet(pos, mem);
    }
  } else {
    writeChar(2, "Memory cell is 15 bit wide");
    return -1;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
int changeAccumulator(int pos)
{
  int plusFlag, num;
  refreshGui(pos);
  if (scanNum(&plusFlag, &num) != 0) {
    writeChar(2, "Not a number!");
    return -1;
  }
  if ((num >= 0) && (num < 0x8000)) {
    accumulator = num;
  } else {
    writeChar(2, "Accumutalor is 15 bit wide");
    return -1;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
int changeInstRegisterCount(int pos)
{
  int plusFlag, num;

  refreshGui(pos);
  if (scanNum(&plusFlag, &num) != 0) {
    writeChar(2, "Not a number!");
    return -1;
  }
  if ((num >= 0) && (num < 0x100)) {
    instructionRegisterCount = num;
  } else {
    writeChar(2, "Accumutalor range: from 0 to 99 (0x63)");
    return -1;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
int scanNum(int *plusFlag, int *n)
{
  char buffer[256];
  int pos = 0;
  int i = 0;

  do {
    read(1,&buffer[i++],1);
  } while (buffer[i - 1] != '\n');

  buffer[i - 1] = '\0';

  if (buffer[0] == '+') {
    pos = 1;
    *plusFlag = 1;
  } else {
    *plusFlag = 0;
  }
  if (sreadInt(buffer + pos, n, 16) != 1) {
    return -1;
  }

  return 0;
}
/*---------------------------------------------------------------------------*/
int memorySave(int position)
{
  char filename[256];
  int i = 0;

  writeChar(1, "Enter save file name: ");

  do {
    read(1,&filename[i++],1);
  } while (filename[i - 1] != '\n');

  filename[i - 1] = '\0';

  if (sc_memorySave(filename) == 0) {
    refreshGui(position);
    writeChar(1,"File successfully saved");
    return 0;
  } else { 
    writeChar(1,"Cannot save file: ");
    writeChar(1, filename);
    return -1;
  }
}
/*---------------------------------------------------------------------------*/
int memoryLoad(int position)
{
  char filename[256];
  int i = 0;

  writeChar(1, "Enter load file name: ");

  do {
    read(1,&filename[i++],1);
  } while (filename[i - 1] != '\n');

  filename[i - 1] = '\0';

  char* ptr1;

  ptr1 = strrchr(filename, '.');

  if (ptr1 != NULL) {
    if (strcmp(ptr1, ".sa") == 0) {
      char* ptr = NULL;
      int size = strlen(filename);
      ptr = malloc(sizeof(char) * size);
      for (i = 0; i < size; i++) {
        ptr[i] = filename[i];
      }
      ptr1[1] = 'o';
      ptr1[2] = '\0';
      char* args[3];
      args[0] = NULL;
      args[1] = filename;
      args[2] = ptr;
      asmTrans(3, args);
    } 
  }

  if (sc_memoryLoad(filename) == 0) {
    refreshGui(position);
    writeChar(1,"File successfully loaded");
    return 0;
  } else {
    writeChar(1,"Cannot load file: ");
    writeChar(1, filename);
    return -1;
  }
}
