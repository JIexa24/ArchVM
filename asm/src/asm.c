/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/asm.h"

int asmTrans(int argc, char** argv)
{
  if (testArgv(argv) == 1) {
    return 1;
  }
  int input                = 0;
  int output               = 0;
  char buffer[SIZE_BUFFER] = {0};
  int ram[sizeRAM]         = {0};
  int counterTokens        = 0;
  int flagign              = 0;
  int i                    = 0;
  int addres               = 0;
  int value                = 0;
  int ret                  = 0;


  if ((input = open(argv[2], O_RDONLY)) == -1) {
    return 1;
  }

  if ((output = open(argv[1], O_WRONLY)) == -1) {
    return 1;
  }

  for (i = 0; i < sizeRAM; i++) {
    ram[i] = 0;
  }

  i = 0;
  do {
    value = 0;
    addres = 0;
    read(input, &buffer[i], sizeof(char));
    if (buffer[i] == TOKENSYMB) {
      if (buffer[i - 1] == TOKENSYMB) {
        continue;
      }
    }
    if (buffer[i] == ' ') {
      if (buffer[i - 1] == ' ') {
        continue;
      }
    }
    if (buffer[i] == EOF & flagign == 0) {
      if (counterTokens == 2) {
        buffer[i] = '\0';
        ret = parsingLine(buffer, &addres, &value);
        if (!ret) {
          ram[addres] = value;
        }
      }
      break;
    }
    if (buffer[i] == '\n' & flagign == 1) {
      flagign = 0;
      i = 0;
      counterTokens = 0;
      continue;
    }
    if (flagign == 0) {
      if (buffer[i] == TOKENSYMB & counterTokens < 2) {
        counterTokens++;
        if (counterTokens == 2) {
          i++;
        }
      }
      if (counterTokens == 2 & (buffer[i] == ';' | buffer[i] == '\n'
          | buffer[i] == ' ' | buffer[i] == TOKENSYMB)) {
        if (buffer[i] == ';' | buffer[i] == ' ' | buffer[i] == TOKENSYMB) {
          flagign = 1;
        }
        buffer[i] = '\0';
        ret = parsingLine(buffer, &addres, &value);
        if (ret == 0 | ret == 2) {
          ram[addres] = value;
        }
        counterTokens = 0;
        i = 0;
      }

      i++;
    }
  } while (1);

  write(output, ram, sizeof(int) * sizeRAM);

  close(input);
  close(output);

  return 0;
}
/*---------------------------------------------------------------------------*/
int testArgv(char *argv[])
{
  char *ptr1 = NULL;
  char *ptr2 = NULL;

  ptr1 = strrchr(argv[1], '.');
  ptr2 = strrchr(argv[2], '.');
  if ((!(strcmp(ptr1, ".o") == 0)) | (!(strcmp(ptr2, ".sa") == 0))) {
    return 1;
  } else {
    return 0;
  }
}
/*---------------------------------------------------------------------------*/
int asmCommand(char *str)
{
  int ret = 0;
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
  } else if (strcmp(str, "CHL") == 0) {
    ret = 0x60;
  } else if (strcmp(str, "SHR") == 0) {
    ret = 0x61;
  } else if (strcmp(str, "RCL") == 0) {
    ret = 0x62;
  } else if (strcmp(str, "RCR") == 0) {
    ret = 0x63;
  } else if (strcmp(str, "NEG") == 0) {
    ret = 0x64;
  } else if (strcmp(str, "ADDC") == 0) {
    ret = 0x65;
  } else if (strcmp(str, "SUBC") == 0) {
    ret = 0x66;
  } else if (strcmp(str, "LOGLC") == 0) {
    ret = 0x67;
  } else if (strcmp(str, "LOGRC") == 0) {
    ret = 0x68;
  } else if (strcmp(str, "RCCL") == 0) {
    ret = 0x69;
  } else if (strcmp(str, "RCCR") == 0) {
    ret = 0x70;
  } else if (strcmp(str, "MOVA") == 0) {
    ret = 0x71;
  } else if (strcmp(str, "MOVR") == 0) {
    ret = 0x72;
  } else if (strcmp(str, "MOVCA") == 0) {
    ret = 0x73;
  } else if (strcmp(str, "MOVCR") == 0) {
    ret = 0x74;
  } else if (strcmp(str, "ADDCT") == 0) { /* !!! */
    ret = 0x75;
  } else if (strcmp(str, "SUBCT") == 0) { /* !!! */
    ret = 0x76;
  } else {
    ret = -1;
  }
  return ret;
}
/*---------------------------------------------------------------------------*/
int strToCommand(char* ptr, int* value)
{
  int command  = 0;
  int operand  = 0;
  int plusFlag = 0;
  int position = 0;
  int tmp      = 0;

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
  char* ptr       = str;
  int command     = 0;
  int operand     = 0;
  int flagCommand = 0;
  int i           = 0;
  char* tmpPtr    = ptr;

  while (1) {
    if (tmpPtr[i] == TOKENSYMB) {
      ptr = tmpPtr + i + 1;
      tmpPtr[i] = '\0';
      break;
    }
    i++;
  }

  sreadInt(tmpPtr, addres, 10);

  if (*addres < 0 | *addres > sizeRAM) {
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
    tmpPtr = ptr + 1;

    if (*tmpPtr == '+') {
      char tmp = tmpPtr[3];

      tmpPtr[3] = '\0';
      sreadInt(tmpPtr + 1, &command, 16);
      tmpPtr[3] = tmp;

      tmpPtr = &tmpPtr[3];
      tmp = tmpPtr[2];
      tmpPtr[2] = '\0';
      sreadInt(tmpPtr, &operand, 16);
      tmpPtr[2] = tmp;

      sc_commandEncode(command, operand, value);
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
    tmpPtr = ptr + 1;

    if (sreadInt(tmpPtr, &operand, 10) == -1) {
      return -1;
    }
    sc_commandEncode(command, operand, value);
  }
  if (command == 0x43) {
    return 2;
  }
  return 0;
}
