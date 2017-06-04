/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/basic.h"
#include "./../../asm/include/asm.h"

int main(int argc, char** argv)
{
  printf("%d %s %s\n", argc, argv[1], argv[2]);
  char dest[SIZE_BUFFER];
  char src[SIZE_BUFFER];
  strcpy(dest, argv[1]);
  strcpy(src, argv[2]);
  char* ptr = strchr(dest, '.');
  ptr[1] = 's';
  ptr[2] = 'a';
  ptr[3] = '\0';
  char *argp[3] = {NULL, dest, src};
  printf("%d %s %s\n", argc, argp[1], argp[2]);
  basicTrans(argc, argp);
  ptr = strchr(src, '.');
  ptr[1] = 's';
  ptr[2] = 'a';
  ptr[3] = '\0';
  ptr = strchr(dest, '.');
  ptr[1] = 'o';
  ptr[2] = '\0';
  argp[1] = dest;
  argp[2] = src;
  printf("%d %s %s\n", argc, dest, src);
  asmTrans(argc, argp);
  return 0;
}
