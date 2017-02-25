#include "./../include/sc_command.h"
#include "./../include/sc_register.h"

/*
  ERR_WRONG_ADDR -1
  ERR_OPEN_FILE -2
  ERR_FILE -3
  ERR_UNCORRECT_COMMAND -4
  ERR_ATTRIBUTE_BIT -5
  ERR_WRONG_FLAG -6

  int localRAM[sizRAM];
  short int sc_register;
  const int correctCommands[] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 
                               0x40, 0x41, 0x42, 0x43,0x52, 0x59};
  const int countCmd = 13;
*/

extern int localRAM[];
extern short int sc_register;

extern int correctCommands[];
    

int sc_commandEncode(int command, int operand, int* value)
{
  int *commandPtr = NULL;/*bsearch(&command, correctCommands, countCmd,
                             sizeof(int), intCompare);*/
  int i; 
  for (i = 0; i < countCmd; i++) {
    if (command == correctCommands[i]) commandPtr = &(correctCommands[i]);
  }
  if (commandPtr != NULL) {
    if (operand > 0x7F) {
      operand &= 0x7F;
      sc_regSet(FLAG_OVERFLOW,1);
    }
    *value = (command << 7) | operand;    
    return 0;
  } else {
    sc_regSet(FLAG_COMMAND, 1);
    return ERR_UNCORRECT_COMMAND;
  }
}
/*---------------------------------------------------------------------------*/
int sc_commandDecode(int value, int* command, int* operand)
{
  void *correctCommand;
  int attribute = (value >> 14) & 1;
  int tmpCommand, tmpOperand, i;

  if (attribute == 0) {
    tmpCommand = (value >> 7) & 0x7F;
    tmpOperand = value & 0x7F;
    for (i = 0; i < countCmd; i ++) {
      if (tmpCommand == correctCommands[i]) correctCommand = &(correctCommands[i]);
    }
    /*correctCommand = bsearch(&tmpCommand, correctCommands, countCmd,
							 sizeof(int), intCompare);*/
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
  return 0;
}

