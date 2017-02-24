#include "./../include/cpu.h"

extern accumulator;
extern int localRAM[];
extern int instructionRegisterCount;

void CU()
{
  int command, operand;
  int flag;
  if (instructionRegisterCount >= sizeRAM) {
    sc_regSet(FLAG_OUTMEM, 1);
    sc_regSet(FLAG_INTERRUPT, 1);
    return;
  }
  if (sc_commandDecode(sc_memory[instructionRegisterCount], &command, &operand) != 0) {
    sc_regSet(FLAG_COMMAND, 1);
    sc_regSet(FLAG_INTERRUPT, 1);
    return;
  }
  if ((operand < 0) && (operand >= sizeRAM)) {
    sc_regSet(FLAG_COMMAND, 1);
    sc_regSet(FLAG_INTERRUPT, 1);
    return;
  }
  if ((command >= 0x30) && (command <= 0x33) || command == 0x52) {
    if (ALU(command, operand) != 0)
      sc_regSet(FLAG_INTERRUPT, 1);
  }	else {
    switch (command) {
      case 0x10: /* READ */

      break;		
      case 0x11: /* WRITE */

      break;	
      case 0x20: /* LOAD */
        accumulator = sc_memory[operand];
      break;
      case 0x21: /* STORE */
        sc_memory[operand] = accumulator;
      break;
      case 0x40: /* JUMP */
        instructionRegisterCount = operand - 1;
      break;
      case 0x41: /* JNEG */
        if (((accumulator >> 14) & 1) == 1) {
          instructionRegisterCount = operand - 1;
        }
      break;
      case 0x42: /* JZ */
        if (accumulator == 0) {
          instructionRegisterCount = operand - 1;
        }
      break;
      case 0x43: /* HALT */
        sc_regSet(FLAG_INTERRUPT, 1);
      break;
      case 0x59: /* JNP */
        sc_regGet(FLAG_ODD, &flag);
        if (flag == 1) {
          instructionRegisterCount = operand - 1;
        }
      break;
    }
  }

}
/*---------------------------------------------------------------------------*/
int ALU(int command, int operand)
{
  if ((operand < 0) || (operand >= 100)) {
    sc_regSet(FLAG_OUTMEM,1);
    return ERR_WRONG_ADDR;
  } else {
    int tmp;
    switch (command) {
      case 0x30: /* ADD */
        accumulator += localRAM[operand];
      break;
 	
      case 0x31: /* SUB */
        if (((localRAM[operand] >> 14) & 1) == 1) {
          tmp = localRAM[operand] | (~0x7FFF);
        } else {
          tmp = localRAM[operand];
        }
        accumulator -= tmp;
        if ((accumulator > ((int)(~0x7FFF))) && (accumulator <= 0x7FFF)) {
          accumulator &= 0x7FFF;
        }
      break;
	
      case 0x33: /* MUL */
        accumulator *= localRAM[operand];
      break;

      case 0x32: /* DIV */
        if (localRAM[operand] != 0) {
          accumulator /= localRAM[operand];
        } else {
          sc_regSet(FLAG_DIVISION, 1);
          return -1;
        }
      break;
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
      case 0x52: 
        tmp = localRAM[operand];
        if (tmp > 0x7FFF) {
          tmp = tmp & 0x7FFF; 
        }
        accumulator = accumulator & tmp;
      break;
    }
    if ((accumulator & 1) == 0) {
      sc_regSet(FLAG_ODD, 0);
    } else {
      sc_regSet(FLAG_ODD, 1);
    }
    if ((accumulator > 0x7FFF) || (accumulator < 0)) {
      accumulator &= 0x7FFF;
      sc_regSet(FLAG_OVERFLOW, 1);
    } else {
      sc_regSet(FLAG_OVERFLOW, 0);
    }
    //sc_regSet(FLAG_ODD, accumulator & 1);
    return 0; 
  }
}
/*---------------------------------------------------------------------------*/
