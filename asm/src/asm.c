/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/asm.h"

int testArgv(char *argv[])
{
	char *ptr1, *ptr2;
	
	ptr1 = strrchr(argv[1], '.');
	ptr2 = strrchr(argv[2], '.');
	if ((strcmp(ptr1, ".o") != 0) || (strcmp(ptr2, ".sa") != 0))
		return -1;
	else
		return 0;
}

int asmCommand(char *str)
{
  int ret;
  if (strcmp(str, "READ") == 0) {
    ret = 0x10;
  } else if (strcmp(str, "WRITE") == 0) {
    ret = 0x11;
  } else if (strcmp(str, "LOAD") == 0) {
    ret = 0x20;
  } else if (strcmp(str, "STORE") == 0) {
    ret = 0x21;
  } else if (strcmp(str, "ADD") == 0) {
    ret = 0x30;
  } else if (strcmp(str, "SUB") == 0) {
    ret = 0x31;
  } else if (strcmp(str, "DIVIDE") == 0) {
    ret = 0x32;
  } else if (strcmp(str, "MUL") == 0) {
    ret = 0x33;
  } else if (strcmp(str, "JUMP") == 0) {
    ret = 0x40;
  } else if (strcmp(str, "JNEG") == 0) {
    ret = 0x41;
  } else if (strcmp(str, "JZ") == 0) {
    ret = 0x42;
  } else if (strcmp(str, "HALT") == 0) {
    ret = 0x43;
  } else if (strcmp(str, "JNP") == 0) {
    ret = 0x59;
  } else if (strcmp(str, "NOT") == 0) {
    ret = 0x51;
  } else if (strcmp(str, "ADD") == 0) {
    ret = 0x52;
  } else if (strcmp(str, "OR") == 0) {
    ret = 0x53;
  } else if (strcmp(str, "XOR") == 0) {
    ret = 0x54;
  } else {
    ret = -1;
  }
  return ret;
}
/*---------------------------------------------------------------------------*/
int strToCommand(char* ptr,int* value)
{
  int command, operand;
  int plusFlag = 0;
  int position = 0;
  int tmp;

  if (*ptr == '+') { 
    position++;
    plusFlag = 1;
  }
  if (sreadInt(ptr + position, &tmp, 16) != 1) {
    return -1;
  }

  operand = tmp & 0x7F;
  command = (tmp >> 8) & 0x7F;
  sc_commandEncode(command, operand, value);
  if (!plusFlag) {
    *value |= 1 << 14;
  }

  return 0;
}
/*---------------------------------------------------------------------------*/
int parsingLine(char* str, int* addres, int* value)
{  
  char *ptr;
  int command, operand;
  int flagCommand = 0;
  ptr = strchr(str, ';');
  if (ptr != NULL) {
    *ptr = '\0';
  }
  ptr = strchr(str, '\n');
  if (ptr != NULL) {
    *ptr = '\0';
  }
  ptr = strtok(str, " \t");
  if (ptr == NULL) {
    return -1;
  }

  /* number of cell */
  if (sreadInt(ptr, addres, 10) != 1) {
    return -1;
  }
  if ((*addres < 0) || (*addres >= sizeRAM))
    return -1;

  /* Get command */
  ptr = strtok(ptr, " \t");
  if (ptr == NULL) {
    return -1;
  } else if (strcmp(ptr, "=") == 0) {
    flagCommand = 1;
  } else {
    command = asmCommand(ptr);
    if (command == -1)
      return -1;
  }

  ptr = strtok(ptr, " \t");
  if (ptr == NULL) {
    return -1;
  }

  if (!flagCommand) {
    if (sreadInt(ptr, &operand, 10) != 1) {
      return -1;
    }
  } else {
    if (strToCommand(ptr, value) == -1) {
      return -1;
    }
  }
  if ((operand < 0) || (operand >= sizeRAM))
    return -1;


  ptr = strtok(ptr, " \t");
  if (ptr != NULL)
    return -1;

  if (!flagCommand) {
    sc_commandEncode(command, operand, value);
  }

  return 0;
}
