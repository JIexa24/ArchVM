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
  } else if (strcmp(str, "NOT") == 0) {
    ret = 0x51;
  } else if (strcmp(str, "ADD") == 0) {
    ret = 0x52;
  } else if (strcmp(str, "OR") == 0) {
    ret = 0x53;
  } else if (strcmp(str, "XOR") == 0) {
    ret = 0x54;
  } else if (strcmp(str, "JNS") == 0) {
    ret = 0x55;
  } else if (strcmp(str, "JC") == 0) {
    ret = 0x56;
  } else if (strcmp(str, "JNC") == 0) {
    ret = 0x57;
  } else if (strcmp(str, "JP") == 0) {
    ret = 0x58;
  } else if (strcmp(str, "JNP") == 0) {
    ret = 0x59;
  }  else if (strcmp(str, "CHL") == 0) {
    ret = 0x60;
  }  else if (strcmp(str, "SHR") == 0) {
    ret = 0x61;
  }  else if (strcmp(str, "RCL") == 0) {
    ret = 0x62;
  }  else if (strcmp(str, "RCR") == 0) {
    ret = 0x63;
  }  else if (strcmp(str, "NEG") == 0) {
    ret = 0x64;
  }  else if (strcmp(str, "ADDC") == 0) {
    ret = 0x65;
  }  else if (strcmp(str, "SUBC") == 0) {
    ret = 0x66;
  }  else if (strcmp(str, "LOGLC") == 0) {
    ret = 0x67;
  }  else if (strcmp(str, "LOGRC") == 0) {
    ret = 0x68;
  } else if (strcmp(str, "RCCL") == 0) {
    ret = 0x69;
  } else if (strcmp(str, "RCCR") == 0) {
    ret = 0x70;
  } else if (strcmp(str, "MOVA") == 0) {
    ret = 0x71;
  }  else if (strcmp(str, "MOVR") == 0) {
    ret = 0x72;
  }  else if (strcmp(str, "MOVCA") == 0) {
    ret = 0x73;
  }  else if (strcmp(str, "MOVCR") == 0) {
    ret = 0x74;
  }  else if (strcmp(str, "ADDCT") == 0) { /* !!! */
    ret = 0x75;
  }  else if (strcmp(str, "SUBCT") == 0) { /* !!! */
    ret = 0x76;
  }  else {
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
  char* ptr = str;
  int command, operand;
  int flagCommand = 0;
  int i = 0;
  
  char* tmpPtr = ptr; 

  while (1) {
    if (tmpPtr[i] == TOKENSYMB) {
      ptr = tmpPtr + i + 1;
      tmpPtr[i] = '\0';
      break;
    }
    i++;
  }

  printf("LOLOLOLOLOLOLOLO %s  ", tmpPtr);
  sreadInt(tmpPtr, addres, 10);
  printf("LOLOLOLOLOLOLOLO %d", *addres);
  if (*addres < 0 || *addres > sizeRAM) {
    return -1;
  }

  i = 0;
  tmpPtr = ptr;
  if (*ptr == '=') {
    flagCommand = 1;
  }
 
  if (flagCommand) {
    while (1) {
      if (tmpPtr[i] == TOKENSYMB) {
        ptr = tmpPtr + i + 1;
        tmpPtr[i] = '\0';
        break;
      }
      i++;
    }
    if (*tmpPtr == '+') {
      sreadInt(tmpPtr + 1, value, 16);
      *value &= 0x7FFF;
    } else {
      sreadInt(tmpPtr, value, 16);
      *value |= (1 << 14);
      *value &= 0x7FFF;
    }
 
  } else {
    while (1) {
      if (tmpPtr[i] == TOKENSYMB) {
        ptr = tmpPtr + i + 1;
        tmpPtr[i] = '\0';
        break;
      }
      i++;
    }

    command = asmCommand(tmpPtr);
    if (command == -1) {
      return -1;
    }
    i = 0;
    tmpPtr = ptr;
  printf("LOLO %s  ", tmpPtr);

    sreadInt(tmpPtr, &operand, 10);

    sc_commandEncode(command, operand, value);
  }
  return 0;
}
