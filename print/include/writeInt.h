/*
  Created by JIexa24 (Alexey R.)
*/
#ifndef WRITE_INT_H
#define WRITE_INT_H

#include <unistd.h>
#include <string.h>

#define SIZE_BUFFER 256

int writeChar(int fd, char* str);
int writeInt(int std, int num, int radix, int znac);
int swriteInt(char* buff, int num, int radix, int znac);

#endif
