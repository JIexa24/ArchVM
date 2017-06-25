/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/cpu.h"

extern int accumulator;
extern int instructionPointer;
extern int writeUse;
extern int writeValue;
extern int position;
extern int cursorX;
extern int cursorY;

int commandHandler(int command, int operand)
{
  int tmp    = 0;
  int tmpMem = 0;
  int flag   = 0;

  switch (command) {
/*--------------------------------------------------------------------------1*/
    case 0x10: /* READ */
      while (readMcell(operand) != 0);
    break;
/*--------------------------------------------------------------------------2*/
    case 0x11: /* WRITE */
      writeUse = 1;
      if (sc_memoryGet(operand, &writeValue) != 0) {
        return -1;
      }
    break;
/*--------------------------------------------------------------------------3*/
    case 0x20: /* LOAD */
      if (sc_memoryGet(operand, &accumulator) != 0) {
        return -1;
      }
      accumulator &= 0x3FFF;
    break;
/*--------------------------------------------------------------------------4*/
    case 0x21: /* STORE */
      tmp = accumulator | (1 << 14);
      if (sc_memorySet(operand, tmp) != 0) {
        return -1;
      }
    break;
/*--------------------------------------------------------------------------5*/
    case 0x30: /* ADD */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }
      tmpMem &= 0x3FFF;
      if (accumulator + tmpMem > 0x3FFF) {
        sc_regSet(FLAG_OVERFLOW, 1);
        accumulator += tmpMem;
        accumulator &= 0x3FFF;
      } else {
        accumulator += tmpMem;
      }
    break;
/*--------------------------------------------------------------------------6*/
    case 0x31: /* SUB */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }
      tmpMem &= 0x3FFF;
      if (accumulator - tmp < 0) {
        sc_regSet(FLAG_OVERFLOW, 1);
        accumulator = 0;
      } else {
        accumulator -= tmpMem;
      }
    break;
/*--------------------------------------------------------------------------7*/
    case 0x32: /* DIV */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }
      if (((tmpMem >> 14) & 1) == 1) {
        tmpMem = tmpMem & (0x3FFF);
      } else {
        tmpMem = tmpMem;
      }
      if (tmpMem > 0) {
        accumulator = accumulator / tmpMem;
      } else {
        sc_regSet(FLAG_DIVISION, 1);
        return -1;
      }
    break;
/*--------------------------------------------------------------------------8*/
    case 0x33: /* MUL */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }
      accumulator = accumulator * (tmpMem & 0x3FFF);
    break;
/*--------------------------------------------------------------------------9*/
    case 0x40: /* JUMP */
      instructionPointer = operand - 1;
    break;
/*-------------------------------------------------------------------------10*/
    case 0x41: /* JNEG */
      if (((accumulator >> 14) & 1) == 1) {
        instructionPointer = operand - 1;
      }
    break;
/*-------------------------------------------------------------------------11*/
    case 0x42: /* JZ */
      if (accumulator == 0) {
        instructionPointer = operand - 1;
      }
    break;
/*-------------------------------------------------------------------------12*/
    case 0x43: /* HALT */
      //flagHalt = 1;
      sc_regSet(FLAG_INTERRUPT, 1);
      instructionPointer--;
      position = instructionPointer;
      cursorX = instructionPointer / 10;
      cursorY = instructionPointer % 10;
      refreshGui(instructionPointer);
    break;
/*-------------------------------------------------------------------------13*/
    case 0x51:  /* NOT */
      accumulator = ~accumulator;
      if (sc_memorySet(operand, accumulator) != 0) {
        return -1;
      }
    break;
/*-------------------------------------------------------------------------14*/
    case 0x52:  /* AND */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
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
        return -1;
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
        return -1;
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
        instructionPointer = operand - 1;
    break;
/*-------------------------------------------------------------------------18*/
    case 0x56:  /* JC */
      sc_regGet(FLAG_OVERFLOW, &flag);
      if (flag == 1) {
        instructionPointer = operand - 1;
      }
    break;
/*-------------------------------------------------------------------------19*/
    case 0x57:  /* JNC */
      sc_regGet(FLAG_OVERFLOW, &flag);
      if (flag == 0) {
        instructionPointer = operand - 1;
      }
    break;
/*-------------------------------------------------------------------------20*/
    case 0x58:  /* JP */
      sc_regGet(FLAG_ODD, &flag);
      if (flag == 0) {
        instructionPointer = operand - 1;
      }
    break;
/*-------------------------------------------------------------------------21*/
    case 0x59: /* JNP */
      sc_regGet(FLAG_ODD, &flag);
      if (flag == 1) {
        instructionPointer = operand - 1;
      }
    break;
/*-------------------------------------------------------------------------22*/
    case 0x60:  /* CHL */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }
      if (tmpMem) {
        tmpMem = tmpMem << 1;
        tmpMem &= 0x7FFF;
      }
      accumulator = tmpMem;
    break;
/*-------------------------------------------------------------------------23*/
    case 0x61:  /* SHR */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }
      tmp = 0;
      if (tmpMem) {
        tmp = (tmpMem >> 14) & 1;
        tmpMem &= 0x3FFF;
        tmpMem = tmpMem >> 1;
      }
      accumulator = tmpMem | (tmp << 14);
    break;
/*-------------------------------------------------------------------------24*/
    case 0x62:  /* RCL */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }
      if (tmpMem) {
        tmp = (tmpMem >> 14) & 1;
        tmpMem = tmpMem << 1 | ((tmpMem >> 13) & 1);
        tmpMem = tmpMem | (tmp << 14);
        tmpMem &= 0x7FFF;
      }
      accumulator = tmpMem;
    break;
/*-------------------------------------------------------------------------25*/
    case 0x63:  /* RCR */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }
      if (tmpMem) {
        tmp = tmpMem & 1;
        tmpMem = tmpMem >> 1 | ((tmpMem & 1) << 13);
        tmpMem = tmpMem | (tmp << 14);
        tmpMem &= 0x7FFF;
      }
      accumulator = tmpMem;
    break;
/*-------------------------------------------------------------------------26*/
    case 0x64:  /* NEG */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }
      if (tmpMem) {
        tmpMem = (~tmpMem + 1);
        tmpMem &= 0x7FFF;
      }
      accumulator = tmpMem;
    break;
/*-------------------------------------------------------------------------27*/
    case 0x65:  /* ADDC */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }

      tmp = tmpMem;

      if (sc_memoryGet(accumulator, &tmpMem) != 0) {
        return -1;
      }

      if (tmp + tmpMem > 0x7FFF) {
        sc_regSet(FLAG_OVERFLOW, 1);
      } else {
        accumulator = tmp + tmpMem;
      }
    break;
/*-------------------------------------------------------------------------28*/
    case 0x66:  /* SUBC */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }

      tmp = tmpMem;

      if (sc_memoryGet(accumulator, &tmpMem) != 0) {
        return -1;
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
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }

      if (tmpMem) {
        tmp = (accumulator >> 14) & 1;
        tmpMem &= 0x3FFF;
        accumulator = (tmpMem << accumulator) | (tmp << 14);
      } else {
        accumulator = tmpMem;
      }
    break;
/*-------------------------------------------------------------------------30*/
    case 0x68:  /* LOGRC */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }

      if (tmpMem) {
        tmp = (accumulator >> 14) & 1;
        tmpMem &= 0x3FFF;
        accumulator = tmpMem >> accumulator | (tmp << 14);
      } else {
        accumulator = tmpMem;
      }
    break;
/*-------------------------------------------------------------------------31*/
    case 0x69:  /* RCCL */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }
      if (tmpMem) {

        if (sc_memoryGet(accumulator, &tmp) != 0) {
          return -1;
        }

        int i = 0;
        for (i = 0; i < tmp; i ++) {
          tmpMem = (tmpMem << 1) & ((tmpMem >> 14) & 1);
        }
        accumulator = tmpMem;
        accumulator &= 0x7FFF;
      } else {
        accumulator = tmpMem;
        accumulator &= 0x7FFF;
      }
    break;
/*-------------------------------------------------------------------------32*/
    case 0x70:  /* RCCR */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }
      if (tmpMem) {
        if (sc_memoryGet(accumulator, &tmp) != 0) {
        return -1;
        }

        int i = 0;
        for (i = 0; i < tmp; i ++) {
          tmpMem = (tmpMem >> 1) & ((tmpMem & 1) << 14);
        }

        accumulator = tmpMem;
        accumulator &= 0x3FFF;
      } else {
        accumulator = tmpMem;
        accumulator &= 0x3FFF;
      }
    break;
/*-------------------------------------------------------------------------33*/
    case 0x71:  /* MOVA */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }
      if (accumulator == operand) {
        return -1;
      }

      if (sc_memorySet(accumulator, tmpMem) != 0) {
        return -1;
      }
      if (sc_memorySet(operand, 0) != 0) {
        return -1;
      }
    break;
/*-------------------------------------------------------------------------34*/
    case 0x72:  /* MOVR */
      if (sc_memoryGet(accumulator, &tmpMem) != 0) {
        return -1;
      }
      if (accumulator == operand) {
        return -1;
      }
      if (sc_memorySet(operand, tmpMem) != 0) {
        return -1;
      }
      if (sc_memorySet(accumulator, 0) != 0) {
        return -1;
      }
    break;
/*-------------------------------------------------------------------------35*/
    case 0x73:  /* MOVCA */
      if (sc_memoryGet(accumulator, &tmpMem) != 0) {
        return -1;
      }
      tmpMem &= 0x3FFF;
      if (tmpMem == operand) {
        return -1;
      }
      if (sc_memoryGet(operand, &tmp) != 0) {
        return -1;
      }

      if (sc_memorySet(tmpMem, tmp) != 0) {
        return -1;
      }
      if (sc_memorySet(operand, 0) != 0) {
        return -1;
      }
    break;
/*-------------------------------------------------------------------------36*/
    case 0x74:  /* MOVCR */
      if (sc_memoryGet(accumulator, &tmpMem) != 0) {
        return -1;
      }
      tmpMem &= 0x3FFF;
      if (tmpMem == operand) {
        return -1;
      }

      if (sc_memoryGet(tmpMem, &tmp) != 0) {
        return -1;
      }

      if (sc_memorySet(operand, tmp) != 0) {
        return -1;
      }
      if (sc_memorySet(tmpMem, 0) != 0) {
        return -1;
      }
    break;
/*-------------------------------------------------------------------------37*/
    case 0x75:  /* ADDC */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }
      tmpMem &= 0x3FFF;

      tmp = tmpMem;
      if (sc_memoryGet(accumulator, &tmpMem) != 0) {
        return -1;
      }
      if (tmp + tmpMem > 0x7FFF) {
        sc_regSet(FLAG_OVERFLOW, 1);
      } else {
        accumulator = tmp + tmpMem;
      }
    break;
/*-------------------------------------------------------------------------38*/
    case 0x76:  /* SUBC */
      if (sc_memoryGet(operand, &tmpMem) != 0) {
        return -1;
      }
      tmpMem &= 0x3FFF;

      tmp = tmpMem;

      if (sc_memoryGet(accumulator, &tmpMem) != 0) {
        return -1;
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
  return 0;
}
