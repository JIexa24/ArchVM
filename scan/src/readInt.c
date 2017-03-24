/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/readInt.h"

int sreadInt(char* buffers, int* num, int radix)
{
  int size = strlen(buffers) - 1;
  int i, k = 0;

  *num = 0;
  for (i = size; i >= 0; i--) {
    if ((buffers[i] >= '0') && (buffers[i] <= '9')) {
      *num += pow(radix, k++) * (buffers[i] - '0');
    } else if ((buffers[i] >= 'A') && (buffers[i] <= 'F')) { 
      *num += pow(radix, k++) * (buffers[i] - 'A' + 10);
    } else {
      return -1;
    }
  }
  
  return 1;
}

