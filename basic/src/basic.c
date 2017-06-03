/*
  Created by JIexa24 (Alexey R.)
*/
#include "basic.h"

var alfabet[26];
int begin = 0;
int end = 99;
int tmp      = 0;
int tmp1       = 0;
char read[11]  = "   READ   \n";
char write[12] = "   WRITE   \n";
char jmp[10]   = "   JMP   \n";
char halt[11]  = "   HALT   \n";

int keywordCode(char *str)
{
  if (strcmp(str, "REM") == 0) {
    return KEYW_REM;
  } else if (strcmp(str, "INPUT") == 0) {
    return KEYW_INPUT;
  } else if (strcmp(str, "OUTPUT") == 0) {
    return KEYW_OUTPUT;
  } else if (strcmp(str, "GOTO") == 0) {
    return KEYW_GOTO;
  } else if (strcmp(str, "IF") == 0) {
    return KEYW_IF;
  } else if (strcmp(str, "LET") == 0) {
    return KEYW_LET;
  } else if ((strcmp(str, "END") == 0) || (strcmp(str, "END\n") == 0)) {
    return KEYW_END;
  } else {
    return KEYW_E;
  }
}
/*---------------------------------------------------------------------------*/
int testArgv(char *argv[])
{
  char *ptr1 = NULL;
  char *ptr2 = NULL;

  ptr1 = strrchr(argv[1], '.');
  ptr2 = strrchr(argv[2], '.');
  if ((!(strcmp(ptr1, ".o") == 0)) | (!(strcmp(ptr2, ".sb") == 0))) {
    return -1;
  } else {
    return 0;
  }
}
/*---------------------------------------------------------------------------*/
int strToCommand(char* ptr, int* value)
{
  int command  = 0;
  int operand  = 0;
  int tmp      = 0;

  if (sreadInt(ptr, &tmp, 16) != 1) {
    return -1;
  }

  operand = tmp & 0x7F;
  command = (tmp >> 8) & 0x7F;
  sc_commandEncode(command, operand, value);

  return 0;
}
/*---------------------------------------------------------------------------*/
int testFile(char* filename)
{
  FILE* file = fopen(filename, "r");
  char c = 0;
  while(c != EOF)
  {
    fscanf(file, "%c", &c);
    if (c >= a & c <= z) {
      return 1;
    }
  }
}
/*---------------------------------------------------------------------------*/
int basicTrans(int argc, char *argv[])
{
  testArgv(argv);
  testFile(argv[2]);
  FILE *input              = NULL;
  FILE *output             = NULL;
  char buffer[SIZE_BUFFER] = {0};
  int ram[sizeRAM]         = {0};
  int i                    = 0;
  int addres               = 5;
  int value                = 0;
  char *ptr = NULL;

  strcpy(buffer, argv[1]);
  ptr = strrchr(buffer, '.');
  buffer[1] = 's';
  buffer[2] = 'a';
  buffer[3] = '\0';

  for (i = 0; i < 26; i++) {
    alfabet[i].variable = 0;
    alfabet[i].name[0] = 'A' + i;
    alfabet[i].name[0] = '\0';
  }

  if ((output = fopen(buffer, "wb")) == NULL) {
    exit(1);
  }
  if ((input = fopen(argv[2], "rb")) == NULL) {
    exit(1);
  }

  for (i = 0; i < sizeRAM; i++) {
    ram[i] = 0;
  }
  i = 0;

  do {
    fread(&buffer[i], sizeof(char), 1, input);
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
    if (buffer[i] == '\n') {
      buffer[i] = '\0';
      ret = parsingLine(buffer, &addres, &value);
      ram[addres] = value;
    }
    i++;
    }
  } while (1);

  return 0;
}
/*---------------------------------------------------------------------------*/
int parsingLine(char* str, FILE *output )
{
  char* ptr    = str;
  int command  = 0;
  int operand  = 0;
  int i        = 0;
  char* tmpPtr = ptr;
  int ret      = 0;
  int cmp      = 0;

  while (1) {
    if (tmpPtr[i] == TOKENSYMB) {
      ptr = tmpPtr + i + 1;
      tmpPtr[i] = '\0';
      break;
    }
    i++;
  }
  tmp = tmp1;
  sreadInt(tmpPtr, &tmp1, 10);
  assert(tmp1 > tmp);

  i = 0;
  tmpPtr = ptr;
  while (1) {
    if (tmpPtr[i] == TOKENSYMB) {
      ptr = tmpPtr + i + 1;
      tmpPtr[i] = '\0';
      break;
    }
    i++;
  }
  ret = keywordCode(tmpPtr);
  assert(ret != KEYW_E);
  tmpPtr = ptr;
  if (ret == KEYW_REM) {
    return 0;
  } else if (ret == KEYW_INPUT) {
    for (i = 0; i < 26; i++) {
      if (!strcmp(alfabet[i].name, tmpPtr)) {
        assert(end - 1 < begin);
        alfabet[i].cell = end--;
        if (alfabet[i].variable == 0) {
         alfabet[i].variable = 1;
        }
        //*addres = begin++;
        //sc_commandEncode(0x10, alfabet[i].cell, value);
        read[0] = begin / 10 - '0';
        read[1] = begin++ % 10 - '0';
        read[8] = alfabet[i].cell % 10 - '0';
        read[9] = alfabet[i].cell % 10 - '0';
        fwrite(read, sizeof(char), 10, output);
        break;
      }
    }
  } else if (ret == KEYW_OUTPUT) {
    for (i = 0; i < 26; i++) {
      if (!strcmp(alfabet[i].name, tmpPtr)) {
        assert(end - 1 < begin);
        assert(alfabet[i].variable == 1);
        //*addres = begin++;
        //sc_commandEncode(0x11, alfabet[i].cell, value);
        write[0] = begin / 10 - '0';
        write[1] = begin++ % 10 - '0';
        write[9] = alfabet[i].cell % 10 - '0';
        write[10] = alfabet[i].cell % 10 - '0';
        fwrite(write, sizeof(char), 11, output);
        break;
      }
    }
  } else if (ret == KEYW_GOTO) {
    //*addres = begin++;
    //sc_commandEncode(0x40, 0, value);
    jmp[0] = begin / 10 - '0';
    jmp[1] = begin++ % 10 - '0';
    jmp[7] = tmpPtr[0];
    jmp[8] = tmpPtr[1];
    fwrite(jmp, sizeof(char), 9, output);
  } else if (ret == KEYW_IF) {

  } else if (ret == KEYW_LET) {

  } else if (ret == KEYW_END) {
    halt[0] = begin / 10 - '0';
    halt[1] = begin++ % 10 - '0';
    halt[8] = '0';
    halt[9] = '0';
    fwrite(halt, sizeof(char), 10, output);
    //*addres = begin++;
    //sc_commandEncode(0x43, 0, value);
  }
  return 0;
}
