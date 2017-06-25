/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/cpu.h"

extern int accumulator;
extern int instructionPointer;
extern int bigChars[];
extern int writeValue;
extern int writeUse;
extern int SCANPRINTRADIX;
static int counterRefresh = 0;

static void printWriteValue()
{
  int command = 0;
  int opcode  = 0;
  int operand = 0;
  mt_gotoXY(1, 23);
  printLine(3);

  mt_gotoXY(1, 23);
  command = (writeValue >> 14) & 1;
  if (writeUse != 0) {
    writeChar(1,"Last WRITE: ");
    if (command == 0) {
      sc_commandDecode(writeValue, &opcode, &operand);
      writeChar(1,"+");
      writeInt(1, opcode, 16, 2);
      writeInt(1, operand, 16, 2);
    } else {
      writeChar(1," ");
      writeInt(1, writeValue & 0x3FFF, SCANPRINTRADIX, 4);
    }
  }
}
/*---------------------------------------------------------------------------*/
void printLine(int ctr){
  int x = 0;
  int y = 0;
  int i = 0;
  int j = 0;

  mt_getscreensize(&y, &x);
  for (j = 0; j < ctr; j++) {
    for (i = 0; i < x; i++)
      writeChar(1," ");
    writeChar(1,"\n");
  }
}
/*---------------------------------------------------------------------------*/
void refreshGuiSt(int position)
{
  mt_clrscr();
  printBoxes();
  printLabels();
  printKeys(48, 14);
  printPointer();
  printAccum();
  printOperation(position);
  printMemory(2, 2, position);
  printFlags(66, 11);
  printWriteValue();
  mt_gotoXY(1, 23);
}
/*---------------------------------------------------------------------------*/
void refreshGui(int position)
{
  counterRefresh++;
  if (counterRefresh % REFRESH == 0) {
    refreshGuiSt(position);
    counterRefresh = 0;
  } else {
    printPointer();
    printAccum();
    printOperation(position);
    printMemory(2, 2, position);
    printFlags(66, 11);
    printWriteValue();
    mt_gotoXY(1, 23);
  }
}
/*---------------------------------------------------------------------------*/
void printAccum()
{
  mt_setfgcolor(ACCUMCOLORFG);
  mt_gotoXY(68, 2);
  writeChar(1, "     ");
  mt_gotoXY(68, 2);
  if (SCANPRINTRADIX == 16) {
    writeInt(1, accumulator & 0x3FFF, SCANPRINTRADIX, 4);
  } else if (SCANPRINTRADIX == 10) {
    writeInt(1, accumulator & 0x3FFF, SCANPRINTRADIX, 5);
  }
  mt_setfgcolor(clr_default);
}
/*---------------------------------------------------------------------------*/
void printBoxes()
{
  bc_box(1, 1, 61, 12);
  bc_box(62, 1, 79, 3);
  bc_box(62, 4, 79, 6);
  bc_box(62, 7, 79, 9);
  bc_box(62, 10, 79, 12);
  bc_box(1, 13, 46, 22);
  bc_box(47, 13, 79, 22);
}
/*---------------------------------------------------------------------------*/
void printPointer()
{
  mt_gotoXY(68, 5);
  mt_setfgcolor(INSTREGCOLORFG);
  writeInt(1, instructionPointer, SCANPRINTRADIX, 4);
  mt_setfgcolor(clr_default);
}
/*---------------------------------------------------------------------------*/
void printKeys(int x, int y)
{
  mt_setfgcolor(KEYCOLORFG);
  mt_gotoXY(x, y);
  writeChar(1, "l  - load    | c   - stop");
  mt_gotoXY(x, y + 1);
  writeChar(1, "s  - save    | x/d - radix");
  mt_gotoXY(x, y + 2);
  writeChar(1, "r  - run / stop");
  mt_gotoXY(x, y + 3);
  writeChar(1, "t  - step");
  mt_gotoXY(x, y + 4);
  writeChar(1, "i  - reset");
  mt_gotoXY(x, y + 5);
  writeChar(1, "F5 - accumulator");
  mt_gotoXY(x, y + 6);
  writeChar(1, "F6 - instruction Pointer");
  mt_gotoXY(x, y + 7);
  writeChar(1, "q  - quit    | Ctrl - \\/z/c");
  mt_setfgcolor(clr_default);
}
/*---------------------------------------------------------------------------*/
void printLabels()
{
  mt_setfgcolor(KEYCOLORFG);
  mt_gotoXY(30, 1);
  writeChar(1, " Memory ");
  mt_gotoXY(64, 1);
  writeChar(1, " accumulator ");
  mt_gotoXY(65, 4);
  writeChar(1, " instPointer ");
  mt_gotoXY(65, 7);
  writeChar(1, " Operation ");
  mt_gotoXY(67, 10);
  writeChar(1, " Flags ");
  mt_gotoXY(48, 13);
  writeChar(1, " Keys: ");
  mt_gotoXY(2, 22);
  writeChar(1, " Input/Output ");
  mt_setfgcolor(clr_default);
}
/*---------------------------------------------------------------------------*/
void printOperation(int position)
{
  int mem       = 0;
  int command   = 0;
  int operand   = 0;
  int isCommand = (mem >> 14) & 1;
  char c        = '+';

  if ((position >= sizeRAM) & (position <= 0)) {
    sc_regSet(FLAG_OUTMEM, 1);
    return;
  }
  sc_memoryGet(position, &mem);


  mt_gotoXY(68, 8);
  if ((position >= 0) & (position < sizeRAM)) {
    if (isCommand == 0) {
      sc_commandDecode(mem, &command, &operand);
      writeChar(1, "        ");
      mt_gotoXY(68, 8);
      mt_setfgcolor(COMMANDCOLORFG);
      write(1, &c, 1);
      writeInt(1, command, 16, 2);
      writeChar(1, " : ");
      mt_setfgcolor(OPERANDCOLORFG);
      writeInt(1, operand, 16, 2);
      mt_setfgcolor(clr_default);
    } else {
      mt_setfgcolor(COMMANDCOLORFG);
      writeChar(1, "        ");
      mt_gotoXY(68, 8);
      writeInt(1, mem & 0x3FFF, 16, 4);
      mt_setfgcolor(clr_default);
    }
  }
}
/*---------------------------------------------------------------------------*/
void printFlags(int x, int y)
{
  int reg = 0;

  mt_gotoXY(x, y);

  sc_regGet(FLAG_OVERFLOW, &reg);
  if (reg == 1) {
    mt_setfgcolor(REGCOLORFG);
    writeChar(1, "O");
    mt_setfgcolor(clr_default);
  } else {
    writeChar(1, " ");
  }

  writeChar(1, " ");
  sc_regGet(FLAG_COMMAND, &reg);
  if (reg == 1) {
    mt_setfgcolor(REGCOLORFG);
    writeChar(1, "E");
    mt_setfgcolor(clr_default);
  } else {
    writeChar(1, " ");
  }

  writeChar(1, " ");
  sc_regGet(FLAG_INTERRUPT, &reg);
  if (reg == 1) {
    mt_setfgcolor(REGCOLORFG);
    writeChar(1, "T");
    mt_setfgcolor(clr_default);
  } else {
    writeChar(1, " ");
  }

  writeChar(1, " ");
  sc_regGet(FLAG_OUTMEM, &reg);
  if (reg == 1) {
    mt_setfgcolor(REGCOLORFG);
    writeChar(1, "M");
    mt_setfgcolor(clr_default);
  } else {
    writeChar(1, " ");
  }

  writeChar(1, " ");
  sc_regGet(FLAG_DIVISION, &reg);
  if (reg == 1) {
    mt_setfgcolor(REGCOLORFG);
    writeChar(1, "Z");
    mt_setfgcolor(clr_default);
  } else {
    writeChar(1, " ");
  }
}
/*---------------------------------------------------------------------------*/
int printMcell(int *bigchars, int pos)
{
  int command      = 0;
  int mem          = 0;
  int i            = 0;
  int opcode       = 0;
  int operand      = 0;
  char str[10]     = {0};
  char c           = 0;
  int indexBigChar = 0;

  mt_setfgcolor(KEYCOLORFG);
  mt_gotoXY(14,13);
  writeChar(1," Cell: ");
  writeInt(1, pos, 16, 2);
  writeChar(1,"( ");
  writeInt(1, pos, 10, 2);
  writeChar(1," ) ");
  mt_setfgcolor(clr_default);

  if ((pos >= sizeRAM) & (pos < 0)) {
    sc_regSet(FLAG_OUTMEM, 1);
    return 1;
  }

  sc_memoryGet(pos, &mem);
  command = (mem >> 14) & 1;
  mem &= 0x3FFF;

  if (command == 0) {
    sc_commandDecode(mem, &opcode, &operand);
    str[0] = '+';
    swriteInt(str + 1, opcode, 16, 2);
    swriteInt(str + 3, operand, 16, 2);
  } else {
    str[0] = ' ';
    swriteInt(str + 1, mem, 16, 4);
  }

  for (i = 0; i < 5; i++) {
    mt_gotoXY(2 + 9 * i, 14);
    indexBigChar = (str[i] == '+') ? 0 : (((str[i] >= '0') && (str[i] <= '9'))
                                          ? (str[i] - '0' + 1)
                                          : ((str[i] >= 'A') &&
                                             (str[i] <= 'F'))
                                             ? (str[i] - 'A' + 11) : -1);
    bc_printbigchar(bigchars + (indexBigChar * 2), 2 + i*9, 14, BIGCHARSCOLORFG,
                      BIGCHARSCOLORBG);
  }

  return 0;
}
/*---------------------------------------------------------------------------*/
void printMemory(int x, int y, int position)
{
  int i       = 0;
  int j       = 0;
  int mem     = 0;
  int command = 0;
  int opcode  = 0;
  int operand = 0;

  mt_setfgcolor(KEYCOLORFG);
  mt_gotoXY(68, 13);

  if (SCANPRINTRADIX == 16) {
    writeChar(1, " HEX ");
  } else if (SCANPRINTRADIX == 10) {
    writeChar(1, " DEC ");
  }

  mt_setfgcolor(clr_default);

  if ((position >= sizeRAM) & (position < 0)) {
    sc_regSet(FLAG_OUTMEM, 1);
    return;
  }

  for (i = 0; i < 10; i++) {
    mt_gotoXY(x, y + i);
    for (j = 0; j < 10; j++) {
      sc_memoryGet(i + j * 10, &mem);
      command = (mem >> 14) & 1;
      mem &= 0x3FFF;

      if ((i + j * 10 ) == position) {
        mt_setfgcolor(TEXTCOLORFG);
        mt_setbgcolor(TEXTCOLORBG);
      }

      if ((i + j * 10 ) == instructionPointer) {
        mt_setfgcolor(INSTREGCOLORFG);
      }

      if (command == 0) {
        int ret = sc_commandDecode(mem, &opcode, &operand);
        writeChar(1, "+");
        writeInt(1, opcode, 16, 2);
        writeInt(1, operand, 16, 2);
      } else if (command == 1) {
        writeChar(1, " ");
        writeInt(1, mem, 16, 4);
      }

      if ((i + j * 10) == position) {
        mt_setfgcolor(clr_default);
        mt_setbgcolor(clr_default);
      }

      if ((i + j * 10 ) == instructionPointer) {
        mt_setfgcolor(clr_default);
      }

      if (j != 9) {
        writeChar(1, " ");
      }
    }
  }
  printMcell(bigChars, position);
}
