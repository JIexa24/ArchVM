/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/sc_command.h"
#include "./../include/sc_register.h"

extern int localRAM[];
extern short int sc_register;
extern int correctCommands[];

int sc_commandEncode(int command, int operand, int* value)
{
  int *commandPtr = NULL;
  int i; 

  for (i = 0; i < countCmd; i++) {
    if (command == correctCommands[i]) commandPtr = &(correctCommands[i]);
  }

  if (commandPtr != NULL) {
    if (operand > 0x7F) {
      operand &= 0x7F;
      sc_regSet(FLAG_OVERFLOW,1);
    }
    if (value != NULL) {
      *value = (command << 7) | operand; 
      sc_regSet(FLAG_COMMAND, 0);
      return 0; 
    }
  } else {
    sc_regSet(FLAG_COMMAND, 1);
    return ERR_UNCORRECT_COMMAND;
  }
  return ERR_WRONG_ADDR;
}
/*---------------------------------------------------------------------------*/
int sc_commandDecode(int value, int* command, int* operand)
{
  void *correctCommand;
  int attribute = (value >> 14) & 1;
  int tmpCommand, tmpOperand, i;
  
  if (command != NULL && operand != NULL) {
    if (attribute == 0) {
      tmpCommand = (value >> 7) & 0x7F;
      tmpOperand = value & 0x7F;
      for (i = 0; i < countCmd; i ++) {
        if (tmpCommand == correctCommands[i]) correctCommand = &(correctCommands[i]);
      }

      if (correctCommand != NULL) {
        *command = tmpCommand;
        *operand = tmpOperand;
      } else {
        sc_regSet(FLAG_COMMAND, 1);
        return ERR_UNCORRECT_COMMAND;
      }
      return 0;
    } else {
      return ERR_ATTRIBUTE_BIT;
    }
  }
  return 0;
}

