#include "./../include/readInt.h"

int sreadInt(char* buffers, int* num, int radix)
{
  int size = strlen(buffers) -1;
  int i, k = 0;
  if (size == 0)
    return 1;

  *num = 0;
  for (i = size - 1; i >= 0; i--) {
    *num += pow(radix, k++) * ((buffers[i] <= '9' && buffers[i] >='0') ? buffers[i] - '0' : (buffers[i] <= 'F' && buffers[i] >='A') ? buffers[i] - 'A' : 0);
  }
  
  return 1;
}

