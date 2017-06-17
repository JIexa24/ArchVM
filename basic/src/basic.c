/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/basic.h"

var alfabet[26];
static int begin       = 0;
static int end         = 99;
static int tmp         = -1;
static int tmp1        = 0;
static char readc[11]  = "   READ   \n";
static char writec[12] = "   WRITE   \n";
static char jmpc[11]   = "   JUMP   \n";
static char haltc[11]  = "   HALT   \n";
static char load[11]  = "   LOAD   \n";
static char store[12] = "   STORE   \n";

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
int testArgvB(char *argv[])
{
  char *ptr1 = NULL;
  char *ptr2 = NULL;

  ptr1 = strrchr(argv[1], '.');
  ptr2 = strrchr(argv[2], '.');
  if ((!(strcmp(ptr1, ".sa") == 0)) | (!(strcmp(ptr2, ".sb") == 0))) {
    return -1;
  } else {
    return 0;
  }
}
/*---------------------------------------------------------------------------*/
int testFile(char* filename)
{
  int fd = open(filename, O_RDONLY);
  char c = '\0';
  while(c != EOF)
  {
    read(fd, &c, sizeof(c));
    if (c >= 'a' & c <= 'z') {
      close(fd);
      return 1;
    }
  }
  close(fd);
  return 0;
}
/*---------------------------------------------------------------------------*/
int basicTrans(int argc, char *argv[])
{
  //if (testFile(argv[2])){return 1;}
  int input                = 0;
  int output               = 0;
  char buffer[SIZE_BUFFER] = {0};
  int i                    = 0;
  int addres               = 5;
  int value                = 0;
  char *ptr                = NULL;
  int ret                  = 0;
  int BR                   = 0;
  tmp                      = -1;
  tmp1                     = 0;
  begin                    = 0;
  end                      = 99;

  if ((input = open(argv[2], O_RDONLY)) == -1) {
    return 1;
  }

  if ((output = open(argv[1], O_WRONLY)) == -1) {
    return 1;
  }

  for (i = 0; i < 26; i++) {
    alfabet[i].variable = 0;
    alfabet[i].name[0] = 'A' + i;
    alfabet[i].name[1] = '\0';
  }

  i = 0;

  do {
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
    if (buffer[i] == '\n' | (buffer[i] == EOF) ) {
      if (buffer[i] == EOF) {
        BR = 1;
      }
      buffer[i] = '\0';
      ret = parsingLineB(buffer, output);
      BR = ret;
      if (BR == 1) break;
      if (BR == 2) return 1;
      i = -1;
    }
    i++;
  } while (1);

  close(input);
  close(output);
  return 0;
}
/*---------------------------------------------------------------------------*/
int parsingLineB(char* str, int output)
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
    } else if (tmpPtr[i] == EOF) {
      return 0;
    }
    i++;
  }
  if (!(str[0] >= '0' & str[0] <= '9')) {
    return 0;
  }
  if (tmp1 > 0)
    tmp = tmp1;
  sreadInt(tmpPtr, &tmp1, 10);
  if (tmp1 <= tmp) {
    return 2;
  }

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
  tmpPtr = ptr;
  if (ret == KEYW_REM) {
    return 0;
  } else if (ret == KEYW_INPUT) {
    for (i = 0; i < 26; i++) {
      if (!strcmp(alfabet[i].name, tmpPtr)) {
        if (end - 1 < begin) {
          return 2;
        }
        alfabet[i].cell = end--;
        if (alfabet[i].variable == 0) {
          alfabet[i].variable = 1;
        }
        readc[0] = begin / 10 + '0';
        readc[1] = begin++ % 10 + '0';
        readc[8] = alfabet[i].cell / 10 + '0';
        readc[9] = alfabet[i].cell % 10 + '0';
        write(output, readc, sizeof(char) * strlen(readc));
        break;
      }
    }
  } else if (ret == KEYW_OUTPUT) {
    for (i = 0; i < 26; i++) {
      if (!strcmp(alfabet[i].name, tmpPtr)) {
        if (end - 1 < begin) {
          return 2;
        }

        if (!(alfabet[i].variable == 1)) {
          return 2;
        }
        writec[0] = begin / 10 + '0';
        writec[1] = begin++ % 10 + '0';
        writec[9] = alfabet[i].cell / 10 + '0';
        writec[10] = alfabet[i].cell % 10 + '0';
        write(output, writec, sizeof(char) * strlen(writec));
        break;
      }
    }
  } else if (ret == KEYW_GOTO) {
    jmpc[0] = begin / 10 + '0';
    jmpc[1] = begin % 10 + '0';
    int cell = (tmpPtr[0] - '0') * 10 + (tmpPtr[1] - '0');
    cell = cell - tmp1;
    cell = cell / 10;
    jmpc[8] = (begin + cell) / 10 + '0';
    jmpc[9] = (begin + cell) % 10 + '0';
    ++begin;
    write(output, jmpc, sizeof(char) * strlen(jmpc));
  } else if (ret == KEYW_IF) {

  } else if (ret == KEYW_LET) {
    int j = 0;
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
    for (i = 0; i < 26; i++) {
      if (!strcmp(alfabet[i].name, tmpPtr)) {
        if (end - 1 < begin) {
          return 2;
        }
        alfabet[i].cell = end--;
        if (alfabet[i].variable == 0) {
          alfabet[i].variable = 1;
        }

        tmpPtr = ptr;
        while (1) {
          if (tmpPtr[i] == TOKENSYMB) {
            ptr = tmpPtr + i + 1;
            tmpPtr[i] = '\0';
            break;
          }
          i++;
        }
        if (!(strcmp(tmpPtr,"=") == 0)) {
          return 2;
        }
        tmpPtr = ptr;
        while (1) {
          if (tmpPtr[i] == TOKENSYMB) {
            ptr = tmpPtr + i + 1;
            tmpPtr[i] = '\0';
            break;
          }
          i++;
        }
        for (j = 0; j < 26; j++) {
          if (!strcmp(alfabet[i].name, tmpPtr)) {
            if (end - 1 < begin) {
              return 2;
            }

            if (!(alfabet[j].variable == 1)) {
              return 2;
            }

          }
        }
        write(output, readc, sizeof(char) * strlen(readc));
        break;
        }
      }
  } else if (ret == KEYW_END) {
    haltc[0] = begin / 10 + '0';
    haltc[1] = begin++ % 10 + '0';
    haltc[8] = '0';
    haltc[9] = '0';
    write(output, haltc, sizeof(char) * strlen(haltc));
    return 1;
  } else if (ret == KEYW_E) {
    return 0;
  }
  return 0;
}
