#include "./../include/sc_command.h"

/*
  ERR_WRONG_ADDR -1
  ERR_OPEN_FILE -2
  ERR_FILE_SIZE -3
  ERR_UNCORRECT_COMMAND -4
  ERR_ATTRIBUTE_BIT -5
  ERR_WRONG_FLAG -6

  int localRAM[sizRAM];
  short int sc_register;
  const int correctCommands[] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 
                               0x40, 0x41, 0x42, 0x43, 0x59};
  const int countCmd = 13;
*/

int sc_commandEncode(int* value, int command, int operand)
{
  void *commandPtr = bsearch(&command, correctCommands, countCmd,
                             sizeof(int), intCompare);
  if (commandPtr != NULL) {
    *value = (command << 7) | operand;
    return 0;
  } else {
    return ERR_UNCORRECT_COMMAND;
  }
}
/*------------------------------------------------------------------------------*/
int sc_commandDecode(int value, int* command, int* operand)
{
void *correctCommand;
int attribute = (value >> 14) & 1;
int tmpCommand, tmpOperand;

  if (attribute == 0) {
    tmpCommand = (value >> 7) & 0x7F;
    tmpOperand = value & 0x7F;
    correctCommand = bsearch(&tmpCommand, correctCommands, countCmd,
							 sizeof(int), intCompare);
    if (correctCommand != NULL) {
      *command = tmpCommand;
      *operand = tmpOperand;
    } else {
      return ERR_UNCORRECT_COMMAND;
    }
  } else {
    return ERR_ATTRIBUTE_BIT;
  }
  return 0;
}

