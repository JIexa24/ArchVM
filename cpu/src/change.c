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
  if (scanNum(&plusFlag, &num) != 0) {
    writeChar(2, "Not a number!");
    return -1;
  }
  if ((num >= 0) && (num < 0x8000)) {
    if (plusFlag) {
      command = (num >> 8) & 0x7F;
      operand = num & 0x7F;
      mem = (command << 7) | operand;
      //writeInt(1, mem, 16, -1);
      //mem &= 0x7FFF;
    } else {
      mem = ((1 << 14) | num);
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
  while (buffer[i - 1] != '\n')  {
    read(1,&buffer[i ++],1);
  }
  buffer[i] = '\0';
  //fgets(buffer, 256, stdin);
  if (buffer[0] == '+') {
    pos = 1;
    *plusFlag = 1;
  } else {
    *plusFlag = 0;
  }
  if (sreadInt(buffer + pos, n, 16) != 1) {
    return -1;
  }
//  if (sscanf(buffer + pos, "%x", n) != 1) {
 //   return -1;
 // }
  return 0;
}
/*---------------------------------------------------------------------------*/
int memorySave(int position)
{
  char filename[256];
  writeChar(1, "Enter save file name: ");

  fgets(filename, 256, stdin);

  filename[strlen(filename) - 1] = '\0';

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
	
  writeChar(1, "Enter save file name: ");
  fgets(filename, 256, stdin);
  filename[strlen(filename) - 1] = '\0';
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
