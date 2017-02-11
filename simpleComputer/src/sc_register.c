#include "../include/sc_register.h"

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

int sc_regInit(void)
{
  sc_register = 0;
  return 0;
}
/*------------------------------------------------------------------------------*/
int sc_regSet(int scRegister, int value)
{
  if ((scRegister >= 0) && (scRegister <=4)) {
    if (value == 1) {
      BITSET(sc_register, scRegister);
    } else if (value == 0) {
      BITCLEAR(sc_register, scRegister);
    } else {
	  return 0;
    }		
  }	else {
    return ERR_WRONG_FLAG;
  }
	return 0;
}
/*------------------------------------------------------------------------------*/
int sc_regGet(int scRegister, int* value)
{
  if ((scRegister >= 0) && (scRegister <=4)) {
    *value = BITCHECK(sc_register, scRegister);
  } else { 
    return ERR_WRONG_FLAG;
  }

  return 0;
}
