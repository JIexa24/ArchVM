/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/cpu.h"

extern int accumulator;
extern int localRAM[];
extern int instructionRegisterCount;
extern short int sc_register;
extern int writeUse;
extern int writeValue;
extern int flagHalt;

int commandHandler(int command, int operand)
{
  int tmp;
  int tmpMem;
  int flag;

  switch (command) {
/*--------------------------------------------------------------------------1*/
    case 0x10: /* READ */
      while (readMcell(operand) != 0);
    break;
/*--------------------------------------------------------------------------2*/
    case 0x11: /* WRITE */
      writeUse = 1;
      sc_memoryGet(operand, &writeValue);
    break;
/*--------------------------------------------------------------------------3*/
    case 0x20: /* LOAD */
      sc_memoryGet(operand, &accumulator);
      accumulator &= 0x3FFF;
    break;
/*--------------------------------------------------------------------------4*/
    case 0x21: /* STORE */
      sc_memorySet(operand, accumulator);
    break;
/*--------------------------------------------------------------------------5*/
    case 0x30: /* ADD */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        break;
      }

      if (accumulator + tmpMem > 0x7FFF) {
        sc_regSet(FLAG_OVERFLOW, 1);
        accumulator += tmpMem;
        accumulator &= 0x7FFF;
      } else {
        accumulator += tmpMem;
      }
    break;
/*--------------------------------------------------------------------------6*/
    case 0x31: /* SUB */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        break;
      }

      if (((tmpMem >> 14) & 1) == 1) {
        tmp = tmpMem | (~0x7FFF);
      } else {
        tmp = tmpMem;
      }
      accumulator -= tmp;
      if ((accumulator > ((int)(~0x7FFF))) && (accumulator <= 0x7FFF)) {
        accumulator &= 0x7FFF;
      }
    break;
/*--------------------------------------------------------------------------7*/
    case 0x32: /* DIV */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        break;
      }

      if (tmpMem != 0) {
        accumulator /= tmpMem;
      } else {
        sc_regSet(FLAG_DIVISION, 1);
        return -1;
      }
    break;
/*--------------------------------------------------------------------------8*/
    case 0x33: /* MUL */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        break;
      }
      accumulator *= tmpMem;
    break;
/*--------------------------------------------------------------------------9*/
    case 0x40: /* JUMP */
      instructionRegisterCount = operand - 1;
    break;
/*-------------------------------------------------------------------------10*/
    case 0x41: /* JNEG */
      if (((accumulator >> 14) & 1) == 1) {
        instructionRegisterCount = operand - 1;
      }
    break;
/*-------------------------------------------------------------------------11*/
    case 0x42: /* JZ */
      if (accumulator == 0) {
        instructionRegisterCount = operand - 1;
      }
    break;
/*-------------------------------------------------------------------------12*/
    case 0x43: /* HALT */
      flagHalt = 1;
      sc_regSet(FLAG_INTERRUPT, 1);
      refreshGui(instructionRegisterCount);
    break;
/*-------------------------------------------------------------------------13*/
    case 0x51:  /* NOT */
      accumulator = ~accumulator;
      if (sc_memorySet(operand, accumulator) != 0) {
        break;
      }
    break;
/*-------------------------------------------------------------------------14*/
    case 0x52:  /* AND */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        break;
      }

      tmp = tmpMem;
      if (tmp > 0x7FFF) {
        tmp = tmp & 0x7FFF;
      }
      accumulator = accumulator & tmp;
    break;
/*-------------------------------------------------------------------------15*/
    case 0x53:  /* OR */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        break;
      }

      tmp = tmpMem;
      if (tmp > 0x7FFF) {
        tmp = tmp & 0x7FFF;
      }
      accumulator = accumulator | tmp;
    break;
/*-------------------------------------------------------------------------16*/
    case 0x54:  /* XOR */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        break;
      }

      tmp = tmpMem;
      if (tmp > 0x7FFF) {
        tmp = tmp & 0x7FFF;
      }
      accumulator = accumulator ^ tmp;
    break;
/*-------------------------------------------------------------------------17*/
    case 0x55:  /* JNS */
      if (accumulator > 0)
        instructionRegisterCount = operand - 1;
    break;
/*-------------------------------------------------------------------------18*/
    case 0x56:  /* JC */
      sc_regGet(FLAG_OVERFLOW, &flag);
      if (flag == 1) {
        instructionRegisterCount = operand - 1;
      }
    break;
/*-------------------------------------------------------------------------19*/
    case 0x57:  /* JNC */
      sc_regGet(FLAG_OVERFLOW, &flag);
      if (flag == 0) {
        instructionRegisterCount = operand - 1;
      }
    break;
/*-------------------------------------------------------------------------20*/
    case 0x58:  /* JP */
      sc_regGet(FLAG_ODD, &flag);
      if (flag == 0) {
        instructionRegisterCount = operand - 1;
      }
    break;
/*-------------------------------------------------------------------------21*/
    case 0x59: /* JNP */
      sc_regGet(FLAG_ODD, &flag);
      if (flag == 1) {
        instructionRegisterCount = operand - 1;
      }
    break;
/*-------------------------------------------------------------------------22*/
    case 0x60:  /* CHL */
      if (accumulator) {
        accumulator = accumulator << 1;
        accumulator &= 0x7FFF;
      }
    break;
/*-------------------------------------------------------------------------23*/
    case 0x61:  /* SHR */
      if (accumulator) {
        accumulator = accumulator >> 1;
        accumulator &= 0x7FFF;
      }
    break;
/*-------------------------------------------------------------------------24*/
    case 0x62:  /* RCL */
      if (accumulator) { 
        tmp = accumulator >> 14 & 1; 
        accumulator = accumulator << 1; 
        accumulator = accumulator & tmp;
        accumulator &= 0x7FFF;
      }
    break;
/*-------------------------------------------------------------------------25*/
    case 0x63:  /* RCR */
      if (accumulator) { 
        tmp = accumulator & 1; 
        accumulator = accumulator >> 1; 
        accumulator = accumulator & (tmp << 14);
        accumulator &= 0x7FFF;
      }
    break;
/*-------------------------------------------------------------------------26*/
    case 0x64:  /* NEG */
      if (accumulator) { 
        accumulator = (~accumulator + 1);
        accumulator &= 0x7FFF;
      }
    break;
/*-------------------------------------------------------------------------27*/
    case 0x65:  /* ADDC */
      if (sc_memoryGet(instructionRegisterCount, &tmpMem) != 0) {
        break;
      }

      tmp = tmpMem;
      sc_memoryGet(accumulator, &tmpMem);
      if (tmp + tmpMem > 0x7FFF) {
        sc_regSet(FLAG_OVERFLOW, 1);
      } else {
        accumulator = tmp + tmpMem;
      }
    break;
/*-------------------------------------------------------------------------28*/
    case 0x66:  /* SUBC */
      if (sc_memoryGet(instructionRegisterCount, &tmpMem) != 0) {
        break;
      }

      tmp = tmpMem;

      if (sc_memoryGet(accumulator, &tmpMem) != 0) {
        break;
      }

      if (((tmpMem >> 14) & 1) == 1) {
        tmpMem = tmpMem | (~0x7FFF);
      } else {
        tmpMem = tmpMem;
      }
      accumulator = tmp - tmpMem;
      if ((accumulator > ((int)(~0x7FFF))) && (accumulator <= 0x7FFF)) {
        accumulator &= 0x7FFF;
      }
    break;
/*-------------------------------------------------------------------------29*/
    case 0x67:  /* LOGLC */
      if (accumulator) {
        sc_memoryGet(instructionRegisterCount, &tmpMem);
        sc_memoryGet(accumulator, &tmp);
        accumulator = tmpMem << tmp;
        accumulator &= 0x7FFF;
      }
    break;
/*-------------------------------------------------------------------------30*/
    case 0x68:  /* LOGRC */
      if (accumulator) {
        sc_memoryGet(instructionRegisterCount, &tmpMem);
        sc_memoryGet(accumulator, &tmp);
        accumulator = tmpMem >> tmp;
      }
    break;
/*-------------------------------------------------------------------------31*/
    case 0x69:  /* RCCL */
      if (accumulator) { 
        if (sc_memoryGet(instructionRegisterCount, &tmpMem) != 0) {
          break;
        }

        if (sc_memoryGet(accumulator, &tmp) != 0) {
          break;
        }

        int i = 0;
        for (i = 0; i < tmp; i ++) {
          tmpMem = (tmpMem << 1) & ((tmpMem >> 14) & 1);
        }
        accumulator = tmpMem;
        accumulator &= 0x7FFF;
      }
    break;
/*-------------------------------------------------------------------------32*/
    case 0x70:  /* RCCR */
      if (accumulator) { 
        if (sc_memoryGet(instructionRegisterCount, &tmpMem) != 0) {
          break;
        }

        if (sc_memoryGet(accumulator, &tmp) != 0) {
          break;
        }

        int i = 0;
        for (i = 0; i < tmp; i ++) {
          tmpMem = (tmpMem >> 1) & ((tmpMem & 1) << 14);
        }

        accumulator = tmpMem;
        accumulator &= 0x7FFF;
      }
    break;
/*-------------------------------------------------------------------------33*/
    case 0x71:  /* MOVA */ 
      if (sc_memoryGet(instructionRegisterCount, &tmpMem) != 0) {
        break;
      }
      if (accumulator == instructionRegisterCount) {
        break;
      }

      sc_memorySet(accumulator, tmpMem);
      sc_memorySet(instructionRegisterCount, 0);
    break;
/*-------------------------------------------------------------------------34*/
    case 0x72:  /* MOVR */ 
      if (sc_memoryGet(accumulator, &tmpMem) != 0) {
        break;
      }
      if (accumulator == instructionRegisterCount) {
        break;
      }
      sc_memorySet(instructionRegisterCount, tmpMem);
      sc_memorySet(accumulator, 0);
    break;
/*-------------------------------------------------------------------------35*/
    case 0x73:  /* MOVCA */ 
      if (sc_memoryGet(accumulator, &tmpMem) != 0) {
        break;
      }
      if (sc_memoryGet(tmpMem, &tmpMem) != 0) {
        break;
      }
      if (tmpMem == instructionRegisterCount) {
        break;
      }
      if (sc_memoryGet(instructionRegisterCount, &tmp) != 0) {
        break;
      }

      sc_memorySet(tmp, tmpMem);
      sc_memorySet(instructionRegisterCount, 0);
    break;
/*-------------------------------------------------------------------------36*/
    case 0x74:  /* MOVCR */ 
      if (sc_memoryGet(accumulator, &tmpMem) != 0) {
        break;
      }
      if (sc_memoryGet(tmpMem, &tmpMem) != 0) {
        break;
      }
      if (tmpMem == instructionRegisterCount) {
        break;
      }

      sc_memorySet(instructionRegisterCount, tmpMem);
      sc_memorySet(tmpMem, 0);
    break;
/*-------------------------------------------------------------------------37*/
    case 0x75:  /* ADDC */ 
      if (sc_memoryGet(instructionRegisterCount, &tmpMem) != 0) {
        break;
      }
      if (sc_memoryGet(tmpMem, &tmpMem) != 0) {
        break;
      }

      tmp = tmpMem;
      sc_memoryGet(accumulator, &tmpMem);
      if (tmp + tmpMem > 0x7FFF) {
        sc_regSet(FLAG_OVERFLOW, 1);
      } else {
        accumulator = tmp + tmpMem;
      }
    break;
/*-------------------------------------------------------------------------38*/
    case 0x76:  /* SUBC */ 
      if (sc_memoryGet(instructionRegisterCount, &tmpMem) != 0) {
        break;
      }
      if (sc_memoryGet(tmpMem, &tmpMem) != 0) {
        break;
      }

      tmp = tmpMem;

      if (sc_memoryGet(accumulator, &tmpMem) != 0) {
        break;
      }

      if (((tmpMem >> 14) & 1) == 1) {
        tmpMem = tmpMem | (~0x7FFF);
      } else {
        tmpMem = tmpMem;
      }
      accumulator = tmp - tmpMem;
      if ((accumulator > ((int)(~0x7FFF))) && (accumulator <= 0x7FFF)) {
        accumulator &= 0x7FFF;
      }
    break;
  }
}
