/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/cpu.h"

extern int accumulator;
extern int instructionRegisterCount;
extern int SCANPRINTRADIX;

void setSignals()
{
  printf("ya tut!\n");
  signal(SIGALRM, timerHand);
  signal(SIGUSR1, ursignalHand);
  signal(SIGUSR2, ursignalHand2);
  signal(SIGWINCH, windHand);
  signal(SIGTERM, killHand); /*kill (default)*/
  signal(SIGINT, killHand);  /*Ctrl-C*/
  signal(SIGTSTP, ursignalHand2); /*Ctrl-Z*/
  signal(SIGQUIT, killHand); /*Ctrl-\*/
}
/*---------------------------------------------------------------------------*/
int changeCell(int pos)
{
  int plusFlag = 0;
  int num      = 0;
  int command  = 0;
  int operand  = 0;
  int mem      = 0;
  refreshGui(pos);
  mt_gotoXY(1, 23);
  printLine(2);

  mt_gotoXY(1, 23);
  writeChar(1, "Enter num: ");
  if (scanNum(&plusFlag, &num) != 0) {
    writeChar(2, "Not a number!");
    return -1;
  }
  if ((num >= 0) & (num < 0x8000)) {
    if (plusFlag) {
      command = (num >> 8) & 0x7F;
      if (num & 0x80) {
        writeChar(2, "Operand is 7 bit wide ( <= 7F). ");
        return -1;
      }
      operand = num & 0x7F;
      if (sc_commandEncode(command, operand, &mem) != 0) {
        writeChar(2, "Wrong command. Aborted. ");
        return -1;
      }
    } else {
      mem = num | 0x4000;
    }
    if(sc_memorySet(pos, mem) != 0) {
      return -1;
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
  int plusFlag = 0;
  int num      = 0;

  refreshGui(pos);

  mt_gotoXY(1, 23);
  printLine(2);

  mt_gotoXY(1, 23);
  writeChar(1, "Change Accum (");
  writeInt(1, SCANPRINTRADIX, 10, -1);
  writeChar(1, "): ");

  if (scanNum(&plusFlag, &num) != 0) {
    writeChar(2, "Not a number!");
    return -1;
  }
  if ((num >= 0) & (num < 0x8000)) {
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
  int plusFlag = 0;
  int num      = 0;
  refreshGui(pos);

  mt_gotoXY(1, 23);
  printLine(2);

  mt_gotoXY(1, 23);
  writeChar(1, "Change Register (");
  writeInt(1, SCANPRINTRADIX, 10, -1);
  writeChar(1, "): ");

  if (scanNum(&plusFlag, &num) != 0) {
    writeChar(2, "Not a number!");
    return -1;
  }
  if ((num >= 0) & (num < sizeRAM)) {
    instructionRegisterCount = num;
  } else {
    writeChar(2, "Instruction range: from 0 to 99 (0x63)");
    return -1;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
int scanNum(int *plusFlag, int *n)
{
  char buffer[SIZE_BUFFER] = {0};
  int pos                  = 0;
  int i                    = 0;

  do {
    read(0, &buffer[i++], 1);
  } while (buffer[i - 1] != '\n');

  buffer[i - 1] = '\0';

  if (buffer[0] == '+') {
    pos = 1;
    *plusFlag = 1;
  } else {
     pos = 0;
    *plusFlag = 0;
  }
  if (sreadInt(buffer + pos, n, SCANPRINTRADIX) != 1) {
    return -1;
  }

  return 0;
}
/*---------------------------------------------------------------------------*/
int memorySave(int position)
{
  char filename[SIZE_BUFFER] = {0};
  int i                      = 0;

  refreshGui(position);
  mt_gotoXY(1, 23);
  printLine(2);

  mt_gotoXY(1, 23);
  writeChar(1, "Enter save file name: ");

  do {
    read(0, &filename[i++], 1);
  } while (filename[i - 1] != '\n');

  filename[i - 1] = '\0';

  if (sc_memorySave(filename) == 0) {
    refreshGui(position);
    writeChar(1,"File successfully saved\n");
    return 0;
  } else {
    writeChar(1,"Cannot save file: ");
    writeChar(1, filename);
    writeChar(1,"\n");
    return -1;
  }
}
/*---------------------------------------------------------------------------*/
int memoryLoad(int position)
{
  char filename[SIZE_BUFFER] = {0};
  int i                      = 0;

  refreshGui(position);

  mt_gotoXY(1, 23);
  printLine(2);

  mt_gotoXY(1, 23);
  writeChar(1, "Enter load file name: ");

  do {
    read(0, &filename[i++], 1);
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
    } else if (strcmp(ptr1, ".sb") == 0) {
       char src[SIZE_BUFFER];
       char dest[SIZE_BUFFER];
       strcpy(src, filename);
       strcpy(dest, filename);
       char* ptr = strchr(dest, '.');
       ptr[1] = 's';
       ptr[2] = 'a';
       ptr[3] = '\0';
       char *argp[3] = {NULL, dest, src};
       basicTrans(3, argp);

       ptr = strchr(src, '.');
       ptr[1] = 's';
       ptr[2] = 'a';
       ptr[3] = '\0';
       ptr = strchr(dest, '.');
       ptr[1] = 'o';
       ptr[2] = '\0';
       argp[1] = dest;
       argp[2] = src;
       asmTrans(3, argp);

       ptr = strchr(filename, '.');
       ptr[1] = 'o';
       ptr[2] = '\0';
    }
  }
  if (sc_memoryLoad(filename) == 0) {
    refreshGui(position);
    writeChar(1,"File successfully loaded\n");
    return 0;
  } else {
    writeChar(1,"Cannot load file: ");
    writeChar(1, filename);
    writeChar(1,"\n");
    return -1;
  }
}
