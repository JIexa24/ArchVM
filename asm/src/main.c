/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/asm.h"
#include <stdio.h>
int main(int argc, char *argv[])
{
  FILE *input, *output;
  char buffer[SIZE_BUFFER];
  int ram[sizeRAM];
  int counterTokens = 0;  
  int flagign = 0;  
  int i = 0;
  int addres = 5, value = 0, ret = 0;

  if (argc != 3) {
    exit(1);
  }
  if (testArgv(argv) != 0) {
    exit(1);
  }
  if ((output = fopen(argv[1], "wb")) == NULL) {
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
    printf("kek %c %d\n", buffer[i], i);
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
    if (buffer[i] == EOF) {
      if (counterTokens == 2) {
        buffer[i] = '\0';
        ret = parsingLine(buffer, &addres, &value);
        printf("!!!!!!!!!!!!!!!!!!! %d !!!!!!!!!!!!!\n", ret);
        if (!ret) {
          ram[addres] = value;
        }
      }
      break;
    }
    if (buffer[i] == '\n' && flagign == 1) {
      flagign = 0;
      i = 0;
      counterTokens = 0;
      continue;
    }
    printf("kek --%d\n", flagign);
    if (flagign == 0) {
      if (buffer[i] == TOKENSYMB) {
        counterTokens++;
        if (counterTokens == 2) {
          i++;
        }
      }
    printf("lol --%d\n", counterTokens);
      if (counterTokens == 2 && (buffer[i] == ';' || buffer[i] == '\n' || buffer[i] == ' ' || buffer[i] == TOKENSYMB)) {
        if (buffer[i] == ';' || buffer[i] == ' ' || buffer[i] == TOKENSYMB) {
          flagign = 1;
        }
        buffer[i] = '\0';
        ret = parsingLine(buffer, &addres, &value);
        if (!ret) {
          ram[addres] = value;
        }
        printf("\n!kek %d %d\n", addres, value);
      }

      i++;
    }
  } while (1);

  fwrite(ram, sizeof(*ram) * sizeRAM, 1, output);

  fclose(input);
  fclose(output);

  return 0;
}
