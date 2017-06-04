/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/readInt.h"

int myPow(int a, int b)
{
  int tmp = a;
  if (b == 0) {
    return 1;
  } else if (b == 1) {
    return a;
  } else {
    int i = 1;

    for (i = 1; i < b; i++)
      a = a * tmp;
    return a;
  }
}
/*---------------------------------------------------------------------------*/
int sreadInt(char* buffers, int* num, int radix)
{
  int size = strlen(buffers) - 1;
  int i = size;
  int k = 0;
  
  *num = 0;
  for (i = size; i >= 0; i--) {
    if ((buffers[i] >= '0') & (buffers[i] <= '9')) {
      *num += myPow(radix, k++) * (buffers[i] - '0');
    } else if ((buffers[i] >= 'A') & (buffers[i] <= 'F')) {
      *num += myPow(radix, k++) * (buffers[i] - 'A' + 10);
    } else {
      return -1;
    }
  }

  return 1;
}
