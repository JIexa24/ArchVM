/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/readInt.h"

int sreadInt(char* buffers, int* num, int radix)
{
  int size = strlen(buffers);
  int i, k = 0;
  if (size == 0)
    return 1;

  *num = 0;
  for (i = size - 1; i >= 0; i--) {
    *num += pow(radix, k++) * ((buffers[i] <= '9' && buffers[i] >= '0') ? buffers[i] - '0' : (buffers[i] <= 'F' && buffers[i] >= 'A') ? (buffers[i] - 'A' + 10) : 0);
  }
  
  return 1;
}

