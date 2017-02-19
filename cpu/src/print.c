#include "./../include/cpu.h"

extern accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern sc_register;

void refreshGui(int position)
{
  mt_clrscr();
  printBoxes();
  printLabels();
  printKeys(48, 14);
  printCounter();

  /* print accumulator */

  mt_gotoXY(70, 2);
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//  printf("%04X", accumulator);
  writeInt(1, accumulator, 16, 4);

  printOperation(position);
  printMemory(2, 2, position);
  printFlags(68, 11);
  printMcell(big_chars, position);
  printWriteValue();
  mt_gotoXY(1, 24);
}
/*------------------------------------------------------------------------------*/
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
/*------------------------------------------------------------------------------*/
void printCounter()
{
  mt_gotoXY(70, 5);
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//  printf("%04X",  instructionRegisterCount);
  writeInt(1, instructionRegisterCount, 16, 4);
}
/*------------------------------------------------------------------------------*/
void printKeys(int x, int y)
{
  mt_gotoXY(x, y);
  write(1, "l  - load", 9);
  mt_gotoXY(x, y + 1);
  write(1, "s  - save", 9);
  mt_gotoXY(x, y + 2);
  write(1, "r  - run", 8);
  mt_gotoXY(x, y + 3);
  write(1, "t  - step", 9);
  mt_gotoXY(x, y + 4);
  write(1, "i  - reset", 10);
  mt_gotoXY(x, y + 5);
  write(1, "F5 - accumulator", 16);
  mt_gotoXY(x, y + 6);
  write(1, "F6 - instructionCounter", 23);
}
/*------------------------------------------------------------------------------*/
void printLabels()
{
  mt_gotoXY(30, 1);
  write(1, " Memory ", 8);
  mt_gotoXY(66, 1);
  write(1, " accumulator ", 13);
  mt_gotoXY(63, 4);
  write(1, " instuctionCounter ", 19);
  mt_gotoXY(68, 7);
  write(1, " Operation ", 11);
  mt_gotoXY(68, 10);
  write(1, " Flags ", 7);
  mt_gotoXY(48, 13);
  write(1, " Keys: ", 7);
}
/*------------------------------------------------------------------------------*/
void printOperation(int position)
{
  if ((position < sizeRAM) && (position >= 0)) {
    sc_regSet(FLAG_OUTMEM, 1);
    return;
  }
  int command = (localRAM[position] >> 7) & 0x7F;
  int operand = localRAM[position] & 0x7F;
  int isCommand = (localRAM[position] >> 14) & 1;
  char c;
	
  mt_gotoXY(68, 8);
  if ((position >= 0) && (position < 100)) {
    if (isCommand == 0) {
      c = '+';
    } else {
      c = ' ';
    }

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//  printf("%c%02X : %02X", c, command, operand);
    write(1, &c, 1);
    writeInt(1, command, 16, 2);
    write(1, " : ", 3);
    writeInt(1, operand, 16, 2);
  }
}
/*------------------------------------------------------------------------------*/
void printFlags(int x, int y)
{
  mt_gotoXY(x, y);
  if (BIT_CHECK(sc_register, FLAG_OVERFLOW) == 1) {
    write(1, "O", 1);
  } else {
    write(1, " ", 1);
  }
  if (BIT_CHECK(sc_register, FLAG_COMMAND) == 1) {
    write(1, "E", 1);
  } else {
    write(1, " ", 1);
  }
  if (BIT_CHECK(sc_register, FLAG_INTERRUPT) == 1) {
    write(1, "V", 1);
  } else {
    write(1, " ", 1);
  }
  if (BIT_CHECK(sc_register, FLAG_OUTMEM) == 1) {
    write(1, "M", 1);
  } else {
    write(1, " ", 1);
  }
  if (BIT_CHECK(sc_register, FLAG_DIVISION) == 1) {
    write(1, "Z", 1);
  } else {
    write(1, " ", 1);
  }
}
/*------------------------------------------------------------------------------*/
int printMcell(int *bigchars, int pos)
{
  if ((pos < sizeRAM) && (pos >= 0)) {
    sc_regSet(FLAG_OUTMEM, 1);
    return;
  }
  int command = (localRAM[pos] >> 14) & 1;
  int mem = localRAM[pos] & 0x3FFF;
  int i, opcode, operand;
  char str[10];
  char c;

  opcode = (mem >> 7) & 0x7F;
  operand = mem & 0x7F;

  if (command == 0) {
    sprintf(str, "+%02X%02X", opcode, operand);
  } else {
    sprintf(str, " %04X", mem);
  }

  for (i = 0; i < 5; i++) {
    mt_gotoXY(2 + 9 * i, 14);
    if (str[i] < 128) {
      bc_printbigchar(bigchars + (str[i] * 2), 2 + i*9, 14, clr_default,
                      clr_default);
    } else {
      return -1;
    }
  }

  return 0;
}
/*------------------------------------------------------------------------------*/
void printMemory(int x, int y, int position)
{
  int i, j;
  int mem, command;
  int opcode, operand;

  if ((position < sizeRAM) && (position >= 0)) {
    sc_regSet(FLAG_OUTMEM, 1);
    return;
  }
  for (i = 0; i < 10; i++) {
    mt_gotoXY(x, y + i);
    for (j = 0; j < 10; j++) {
      mem = localRAM[i*10+j] & 0x3FFF;
      command = (localRAM[i*10+j] >> 14) & 1;
      opcode = (mem >> 7) & 0x7F;
      operand = mem & 0x7F;
      if ((i * 10 + j) == position) {
        mt_setfgcolor(clr_black);
        mt_setbgcolor(clr_red);
      }
      if (command == 0) {
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//      printf("+%02X%02X", opcode, operand);
        write(1, "+", 1);
        writeInt(1, opcode, 16, 2);
        writeInt(1, operand, 16, 2);
      } else {
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//      printf(" %02X%02X", opcode, operand);
        write(1, " ", 1);
        writeInt(1, opcode, 16, 2);
        writeInt(1, operand, 16, 2);
      }
      if ((i * 10 + j) == position) {
        mt_setfgcolor(clr_default);
        mt_setbgcolor(clr_default);
      }

      if (j != 9) {
        write(1, " ", 1);
      }
    }
  }
}
