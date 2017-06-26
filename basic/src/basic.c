/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/basic.h"

static var alfabet[26];
static memMap map[SIZE_BUFFER];
static int collision   = 0;
static int indexmap    = 0;
static int begin       = 0;
static int end         = 99;
static int tmp         = -1;
static int tmp1        = 0;
static char readc[11]  = "   READ   \n";
static char writec[12] = "   WRITE   \n";
static char jmpc[11]   = "   JUMP   \n";
static char jneg[11]   = "   JNEG   \n";
static char jns[10]    = "   JNS   \n";
static char haltc[11]  = "   HALT   \n";
static char load[11]   = "   LOAD   \n";
static char store[12]  = "   STORE   \n";
static char sub[10]    = "   SUB   \n";
static char jz[9]      = "   JZ   \n";

volatile int keywordCode(char *str)
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
  int count = 1;
  while(count != 0)
  {
    count = read(fd, &c, sizeof(c));
    if (c >= 'a' & c <= 'z') {
      close(fd);
      return 1;
    }
  }
  close(fd);
  return 0;
}
/*---------------------------------------------------------------------------*/
volatile int basicTrans(int argc, char *argv[])
{
  if (testFile(argv[2])) {
    return 1;
  }
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
  collision                = 0;
  indexmap                 = 0;

  FILE* Crutch = fopen(argv[2], "r");
  fclose(Crutch);
  if ((input = open(argv[2], O_RDONLY)) == -1) {
    return 1;
  }

  Crutch = fopen(argv[1], "w");
  fclose(Crutch);
  if ((output = open(argv[1], O_WRONLY)) == -1) {
    return 1;
  }

  for (i = 0; i < 26; i++) {
    alfabet[i].variable = 0;
    alfabet[i].name[0] = 'A' + i;
    alfabet[i].name[1] = '\0';
  }
  for (i = 0; i < SIZE_BUFFER; i++) {
    map[i].real = -1;
    map[i].expect = -1;
  }

  i = 0;

  do {
    int readcount = read(input, &buffer[i], sizeof(char));
    if (readcount == 0) {
      break;
    }

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
volatile int parsingLineB(char* str, int output)
{
  char* ptr    = str;
  int command  = 0;
  int operand  = 0;
  int i        = 0;
  int j        = 0;
  char* tmpPtr = ptr;
  int ret      = 0;
  int cmp      = 0;
  int flagJump = 0;
  char* op     = NULL;

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

  if (ret == KEYW_IF) {
    i = 0;
    while (1) {
      if (tmpPtr[i] == TOKENSYMB) {
        ptr = tmpPtr + i + 1;
        tmpPtr[i] = '\0';
        break;
      }
      i++;
    }
    if (*tmpPtr >= 'A' & *tmpPtr <= 'Z') {
      for (i = 0; i < 26; i++) {
        if (!strcmp(alfabet[i].name, tmpPtr)) {
          if (!(alfabet[i].variable == 1)) {
            return 2;
          }
          tmpPtr = ptr;
          j = 0;
          while (1) {
            if (tmpPtr[j] == TOKENSYMB) {
              ptr = tmpPtr + j + 1;
              tmpPtr[j] = '\0';
              break;
            }
            j++;
          }
          op = tmpPtr;
          tmpPtr = ptr;
          load[0] = (begin - collision) / 10 + '0';
          load[1] = (begin++ - collision) % 10 + '0';
          load[8] = alfabet[i].cell / 10 + '0';
          load[9] = alfabet[i].cell % 10 + '0';
          write(output, load, sizeof(char) * strlen(load));
          j = 0;
          while (1) {
            if (tmpPtr[j] == TOKENSYMB) {
              ptr = tmpPtr + j + 1;
              tmpPtr[j] = '\0';
              break;
            }
            j++;
          }
          if (*tmpPtr >= 'A' & *tmpPtr <= 'Z') {
            for (j = 0; j < 26; i++) {
              if (!strcmp(alfabet[j].name, tmpPtr)) {
                tmpPtr = ptr;
                if (!(alfabet[j].variable == 1)) {
                  return 2;
                }
                sub[0] = (begin - collision) / 10 + '0';
                sub[1] = (begin++ - collision) % 10 + '0';
                sub[7] = alfabet[j].cell / 10 + '0';
                sub[8] = alfabet[j].cell % 10 + '0';
                write(output, sub, sizeof(char) * strlen(sub));
                break;
              }
            }
          } else {
            int number = atoi(tmpPtr);
            int addr = end--;
            char buf[4];
            swriteInt(buf, number, 16, 4);
            char s = (addr) / 10 + '0';
            write(output, &s, 1);
            s = (addr) % 10 + '0';
            write(output, &s, 1);
            write(output, TOKENSYMBS, 1);
            write(output, "=", 1);
            write(output, TOKENSYMBS, 1);
            write(output, buf, 4);
            write(output, "\n", 1);

            sub[0] = (begin - collision) / 10 + '0';
            sub[1] = (begin++ - collision) % 10 + '0';
            sub[7] = addr / 10 + '0';
            sub[8] = addr % 10 + '0';
            write(output, sub, sizeof(char) * strlen(sub));
          }
        }
      }
    } else {
      int number = atoi(tmpPtr);
      int addr = end--;
      char buf[4];
      swriteInt(buf, number, 16, 4);
      char s = (addr) / 10 + '0';
      write(output, &s, 1);
      s = (addr) % 10 + '0';
      write(output, &s, 1);
      write(output, TOKENSYMBS, 1);
      write(output, "=", 1);
      write(output, TOKENSYMBS, 1);
      write(output, buf, 4);
      write(output, "\n", 1);
      load[0] = (begin - collision) / 10 + '0';
      load[1] = (begin++ - collision) % 10 + '0';
      load[8] = addr / 10 + '0';
      load[9] = addr % 10 + '0';
      write(output, load, sizeof(char) * strlen(load));

      tmpPtr = ptr;
      j = 0;
      while (1) {
        if (tmpPtr[j] == TOKENSYMB) {
          ptr = tmpPtr + j + 1;
          tmpPtr[j] = '\0';
          break;
        }
        j++;
      }
       op = tmpPtr;
      tmpPtr = ptr;
      j = 0;
      while (1) {
        if (tmpPtr[j] == TOKENSYMB) {
          ptr = tmpPtr + j + 1;
          tmpPtr[j] = '\0';
          break;
        }
        j++;
      }
      if (*tmpPtr >= 'A' & *tmpPtr <= 'Z') {
        for (j = 0; j < 26; i++) {
          if (!strcmp(alfabet[j].name, tmpPtr)) {
            tmpPtr = ptr;
            if (!(alfabet[j].variable == 1)) {
              return 2;
            }
            sub[0] = (begin - collision) / 10 + '0';
            sub[1] = (begin++ - collision) % 10 + '0';
            sub[7] = alfabet[j].cell / 10 + '0';
            sub[8] = alfabet[j].cell % 10 + '0';
            write(output, sub, sizeof(char) * strlen(sub));
            break;
          }
        }
      } else {
        number = atoi(tmpPtr);
        addr = end--;

        swriteInt(buf, number, 16, 4);
        char s = (addr) / 10 + '0';
        write(output, &s, 1);
        s = (addr) % 10 + '0';
        write(output, &s, 1);
        write(output, TOKENSYMBS, 1);
        write(output, "=", 1);
        write(output, TOKENSYMBS, 1);
        write(output, buf, 4);
        write(output, "\n", 1);
        sub[0] = (begin - collision) / 10 + '0';
        sub[1] = (begin++ - collision) % 10 + '0';
        sub[7] = addr / 10 + '0';
        sub[8] = addr % 10 + '0';
        write(output, sub, sizeof(char) * strlen(sub));
      }
    }
    tmpPtr = ptr;
    j = 0;
    while (1) {
      if (tmpPtr[j] == TOKENSYMB) {
        ptr = tmpPtr + j + 1;
        tmpPtr[j] = '\0';
        break;
      }
      j++;
    }
    ret = keywordCode(tmpPtr);
    tmpPtr = ptr;
    flagJump = 1;
  }

  if (ret == KEYW_REM) {
    map[indexmap].real = -1;
    map[indexmap].expect = tmp1;
    ++indexmap;
  //  ++collision;
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
        map[indexmap].real = begin;
        map[indexmap].expect = tmp1;
        ++indexmap;
        readc[0] = (begin - collision) / 10 + '0';
        readc[1] = (begin++ - collision) % 10 + '0';
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
        map[indexmap].real = begin;
        map[indexmap].expect = tmp1;
        ++indexmap;
        writec[0] = (begin - collision) / 10 + '0';
        writec[1] = (begin++ - collision) % 10 + '0';
        writec[9] = alfabet[i].cell / 10 + '0';
        writec[10] = alfabet[i].cell % 10 + '0';
        write(output, writec, sizeof(char) * strlen(writec));
        break;
      }
    }
  } else if (ret == KEYW_GOTO) {
    if (flagJump == 1) {
      flagJump = 0;
      if (!strcmp(op, ">")) {
        jz[0] = (begin - collision) / 10 + '0';
        jz[1] = (begin - collision) % 10 + '0';
        jz[6] = (begin + 3) / 10 + '0';
        jz[7] = (begin++ + 3) % 10 + '0';
        write(output, jz, sizeof(char) * strlen(jz));
        jneg[0] = (begin - collision) / 10 + '0';
        jneg[1] = (begin - collision) % 10 + '0';
        jneg[8] = (begin + 2) / 10 + '0';
        jneg[9] = (begin++ + 2) % 10 + '0';
        write(output, jneg, sizeof(char) * strlen(jneg));
      } else if (!strcmp(op, "<")) {
        jns[0] = (begin - collision) / 10 + '0';
        jns[1] = (begin - collision) % 10 + '0';
        jns[7] = (begin + 3) / 10 + '0';
        jns[8] = (begin++ + 3) % 10 + '0';
        write(output, jns, sizeof(char) * strlen(jns));
        jz[0] = (begin - collision) / 10 + '0';
        jz[1] = (begin - collision) % 10 + '0';
        jz[6] = (begin + 2) / 10 + '0';
        jz[7] = (begin++ + 2) % 10 + '0';
        write(output, jz, sizeof(char) * strlen(jz));
      } else if (!strcmp(op, "=")) {
        jneg[0] = (begin - collision) / 10 + '0';
        jneg[1] = (begin - collision) % 10 + '0';
        jneg[8] = (begin + 3) / 10 + '0';
        jneg[9] = (begin++ + 3) % 10 + '0';
        write(output, jneg, sizeof(char) * strlen(jneg));
        jns[0] = (begin - collision) / 10 + '0';
        jns[1] = (begin - collision) % 10 + '0';
        jns[7] = (begin + 2) / 10 + '0';
        jns[8] = (begin++ + 2) % 10 + '0';
        write(output, jns, sizeof(char) * strlen(jns));
      } else {
        return 1;
      }
    }
    jmpc[0] = (begin - collision) / 10 + '0';
    jmpc[1] = (begin - collision) % 10 + '0';
    map[indexmap].real = begin;
    map[indexmap].expect = tmp1;
    ++indexmap;
    int cell = (tmpPtr[0] - '0') * 10 + (tmpPtr[1] - '0');
    for (i = 0; i < indexmap; i++) {
      if ((cell == map[i].expect)) {
        if (map[i].real == -1) {
          return 2;
        }
        cell = (map[i].real);
        jmpc[8] = (cell) / 10 + '0';
        jmpc[9] = (cell) % 10 + '0';
        break;
      }
    }
    ++begin;
    write(output, jmpc, sizeof(char) * strlen(jmpc));
  } else if (ret == KEYW_LET) {

  } else if (ret == KEYW_END) {
    map[indexmap].real = begin;
    map[indexmap].expect = tmp1;
    ++indexmap;
    haltc[0] = (begin - collision) / 10 + '0';
    haltc[1] = (begin++ - collision) % 10 + '0';
    haltc[8] = '0';
    haltc[9] = '0';
    write(output, haltc, sizeof(char) * strlen(haltc));
    return 0;
  } else if (ret == KEYW_E) {
    return 0;
  }
  return 0;
}
