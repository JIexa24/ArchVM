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
  printf("%04X", accumulator);
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
  printf("%04X",  instructionRegisterCount);
}
/*------------------------------------------------------------------------------*/
void printKeys(int x, int y)
{
  mt_gotoXY(x, y);
  printf("l  - load");
  mt_gotoXY(x, y + 1);
  printf("s  - save");
  mt_gotoXY(x, y + 2);
  printf("r  - run");
  mt_gotoXY(x, y + 3);
  printf("t  - step");
  mt_gotoXY(x, y + 4);
  printf("i  - reset");
  mt_gotoXY(x, y + 5);
  printf("F5 - accumulator");
  mt_gotoXY(x, y + 6);
  printf("F6 - instructionCounter");
}
/*------------------------------------------------------------------------------*/
void printLabels()
{
  mt_gotoXY(30, 1);
  printf(" Memory ");
  mt_gotoXY(66, 1);
  printf(" accumulator ");
  mt_gotoXY(63, 4);
  printf(" instuctionCounter ");
  mt_gotoXY(68, 7);
  printf(" Operation ");
  mt_gotoXY(68, 10);
  printf(" Flags ");
  mt_gotoXY(48, 13);
  printf(" Keys: ");
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
    printf("%c%02X : %02X", c, command, operand);
  }
}
/*------------------------------------------------------------------------------*/
void printFlags(int x, int y)
{
  mt_gotoXY(x, y);
  if (BIT_CHECK(sc_register, FLAG_OVERFLOW) == 1) {
    printf("O");
  } else {
    printf(" ");
  }
  if (BIT_CHECK(sc_register, FLAG_COMMAND) == 1) {
    printf("E");
  } else {
    printf(" ");
  }
  if (BIT_CHECK(sc_register, FLAG_INTERRUPT) == 1) {
    printf("V");
  } else {
    printf(" ");
  }
  if (BIT_CHECK(sc_register, FLAG_OUTMEM) == 1) {
    printf("M");
  } else {
    printf(" ");
  }
  if (BIT_CHECK(sc_register, FLAG_DIVISION) == 1) {
    printf("Z");
  } else {
    printf(" ");
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
        printf("+%02X%02X", opcode, operand);
      } else {
        printf(" %02X%02X", opcode, operand);
      }
      if ((i * 10 + j) == position) {
        mt_setfgcolor(clr_default);
        mt_setbgcolor(clr_default);
      }

      if (j != 9) {
        printf(" ");
      }
    }
  }
}
