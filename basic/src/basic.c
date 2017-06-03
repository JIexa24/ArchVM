#include "basic.h"

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
