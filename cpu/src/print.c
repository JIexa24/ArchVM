/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/cpu.h"

extern int accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern short int sc_register;
extern int bigChars[];
extern int writeValue;
extern int writeUse;

static void printWriteValue()
{
  int command, opcode, operand;
  mt_gotoXY(1, 23);
  command = (writeValue >> 14) & 1;
  opcode = (writeValue >> 7) & 0x7F;
  operand = writeValue & 0x7F;
  if (writeUse != 0) {
    writeChar(1,"Last WRITE: ");
    if (command == 0) {
      writeChar(1,"+");
      writeInt(1, opcode, 16, 2);
      writeInt(1, operand, 16, 2);       
    } else {
      writeChar(1," ");
      writeInt(1, opcode, 16, 2);
      writeInt(1, operand, 16, 2);
    }	
  }
}

void refreshGui(int position)
{
  mt_clrscr();
  printBoxes();
  printLabels();
  printKeys(48, 14);
  printCounter();

  /* print accumulator */

  mt_gotoXY(70, 2);
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//  printf("%04X", accumulator);
  writeInt(1, accumulator, 16, 4);

  printOperation(position);
  printMemory(2, 2, position);
  printFlags(68, 11);
  printMcell(bigChars, position);
  printWriteValue();
  mt_gotoXY(1, 24);
}
/*---------------------------------------------------------------------------*/
void printBoxes()
{
  bc_box(1, 1, 61, 12);
  bc_box(62, 1, 82, 3);
  bc_box(62, 4, 82, 6);
  bc_box(62, 7, 82, 9);
  bc_box(62, 10, 82, 12);
  bc_box(1, 13, 46, 22);
  bc_box(47, 13, 82, 22);
}
/*---------------------------------------------------------------------------*/
void printCounter()
{
  mt_gotoXY(70, 5);
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//  printf("%04X",  instructionRegisterCount);
  writeInt(1, instructionRegisterCount, 16, 4);
}
/*---------------------------------------------------------------------------*/
void printKeys(int x, int y)
{
  mt_gotoXY(x, y);
  writeChar(1, "l  - load");
  mt_gotoXY(x, y + 1);
  writeChar(1, "s  - save");
  mt_gotoXY(x, y + 2);
  writeChar(1, "r  - run");
  mt_gotoXY(x, y + 3);
  writeChar(1, "t  - step");
  mt_gotoXY(x, y + 4);
  writeChar(1, "i  - reset");
  mt_gotoXY(x, y + 5);
  writeChar(1, "F5 - accumulator");
  mt_gotoXY(x, y + 6);
  writeChar(1, "F6 - instructionCounter");
}
/*---------------------------------------------------------------------------*/
void printLabels()
{
  mt_gotoXY(30, 1);
  writeChar(1, " Memory ");
  mt_gotoXY(66, 1);
  writeChar(1, " accumulator ");
  mt_gotoXY(63, 4);
  writeChar(1, " instuctionCounter ");
  mt_gotoXY(68, 7);
  writeChar(1, " Operation ");
  mt_gotoXY(68, 10);
  writeChar(1, " Flags ");
  mt_gotoXY(48, 13);
  writeChar(1, " Keys: ");
}
/*---------------------------------------------------------------------------*/
void printOperation(int position)
{
  if ((position >= sizeRAM) && (position <= 0)) {
    sc_regSet(FLAG_OUTMEM, 1);
    return;
  }
  int command = (localRAM[position] >> 7) & 0x7F;
  int operand = localRAM[position] & 0x7F;
  int isCommand = (localRAM[position] >> 14) & 1;
  char c;
	
  mt_gotoXY(68, 8);
  if ((position >= 0) && (position < sizeRAM)) {
    if (isCommand == 0) {
      c = '+';
    } else {
      c = ' ';
    }

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//  printf("%c%02X : %02X", c, command, operand);
    write(1, &c, 1);
    writeInt(1, command, 16, 2);
    writeChar(1, " : ");
    writeInt(1, operand, 16, 2);
  }
}
/*---------------------------------------------------------------------------*/
void printFlags(int x, int y)
{
  mt_gotoXY(x, y);
  if (BITCHECK(sc_register, FLAG_OVERFLOW) == 1) {
    writeChar(1, "O");
  } else {
    writeChar(1, " ");
  }
  if (BITCHECK(sc_register, FLAG_COMMAND) == 1) {
    writeChar(1, "E");
  } else {
    writeChar(1, " ");
  }
  if (BITCHECK(sc_register, FLAG_INTERRUPT) == 1) {
    writeChar(1, "V");
  } else {
    writeChar(1, " ");
  }
  if (BITCHECK(sc_register, FLAG_OUTMEM) == 1) {
    writeChar(1, "M");
  } else {
    writeChar(1, " ");
  }
  if (BITCHECK(sc_register, FLAG_DIVISION) == 1) {
    writeChar(1, "Z");
  } else {
    writeChar(1, " ");
  }
}
/*---------------------------------------------------------------------------*/
int printMcell(int *bigchars, int pos)
{
  if ((pos >= sizeRAM) && (pos < 0)) {
    sc_regSet(FLAG_OUTMEM, 1);
    return 1;
  }
  int command = (localRAM[pos] >> 14) & 1;
  int mem = localRAM[pos] & 0x3FFF;
  int i, opcode, operand;
  char str[10];
  char c;

  opcode = (mem >> 7) & 0x7F;
  operand = mem & 0x7F;

  if (command == 0) {
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//    sprintf(str, "+%02X%02X", opcode, operand);
    str[0] = '+';
    swriteInt(str + 1, opcode, 16, 2);
    swriteInt(str + 3, operand, 16, 2);
  } else {
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//    sprintf(str, " %04X", mem);
    str[0] = ' ';
    swriteInt(str + 1, mem, 16, 4);
  }

  for (i = 0; i < 5; i++) {
    mt_gotoXY(2 + 9 * i, 14);
    if (str[i] < 128) {

      bc_printbigchar(bigchars + (str[i] * 2), 2 + i*9, 14, clr_green,
                      clr_default);
    } else {
      return -1;
    }
  }

  return 0;
}
/*---------------------------------------------------------------------------*/
void printMemory(int x, int y, int position)
{
  int i, j;
  int mem, command;
  int opcode, operand;

  mt_gotoXY(18,13);
  writeChar(1,"Cell: ");
  writeInt(1, position, 16, 2);

  if ((position >= sizeRAM) && (position < 0)) {
    sc_regSet(FLAG_OUTMEM, 1);
    return;
  }
  for (i = 0; i < 10; i++) {
    mt_gotoXY(x, y + i);
    for (j = 0; j < 10; j++) {
/*
      mem = localRAM[i*10+j] & 0x3FFF;
      command = (localRAM[i*10+j] >> 14) & 1;
*/
      mem = localRAM[i+j*10] & 0x3FFF;
      command = (localRAM[i+j*10] >> 14) & 1;
      opcode = (mem >> 7) & 0x7F;
      operand = mem & 0x7F;
      if ((i + j * 10 ) == position) {
        mt_setfgcolor(clr_black);
        mt_setbgcolor(clr_green);
      }
      if ((i + j * 10 ) == instructionRegisterCount) {
        mt_setfgcolor(clr_yellow);
      }
    
      if (command == 0) {
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//      printf("+%02X%02X", opcode, operand);
        writeChar(1, "+");
        writeInt(1, opcode, 16, 2);
        writeInt(1, operand, 16, 2);
      } else {
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//      printf(" %02X%02X", opcode, operand);
        writeChar(1, " ");
        writeInt(1, opcode, 16, 2);
        writeInt(1, operand, 16, 2);
      }
      if ((i + j * 10) == position) {
        mt_setfgcolor(clr_default);
        mt_setbgcolor(clr_default);
      }
      if ((i + j * 10 ) == instructionRegisterCount) {
        mt_setfgcolor(clr_default);
      }

      if (j != 9) {
        writeChar(1, " ");
      }
    }
  }
}
