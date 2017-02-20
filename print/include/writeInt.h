#ifndef WRITE_INT_H
#define WRITE_INT_H

#include <unistd.h>

#define SIZE_BUFFER 256

int writeInt(int std, int num, int radix, int znac);
int swriteInt(char* buff, int num, int radix, int znac);

#endif
