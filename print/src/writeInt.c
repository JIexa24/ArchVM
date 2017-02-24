#include "./../include/writeInt.h"

int writeInt(int std, int num, int radix, int znac)
{
  if (num == 0) {
    write(std, "0", 1);
    return 1;
  }
  
  char sign = '-';

  char buffer[SIZE_BUFFER];
  int counter = SIZE_BUFFER;

  if (radix == 10) {
    if (num < 0) {
      write(std, &sign, 1);
      num = -num;
    }
  }

  while (num) {
    if (num % radix > 9) {
      buffer[--counter] = 'A' + num % radix - 10;
      num /= radix;
    } else {
      buffer[--counter] = '0' + (num % radix);
      num /= radix;
    }
  }
  if (znac > -1) {
    if ((SIZE_BUFFER - counter) < znac) {
      znac = znac - SIZE_BUFFER + counter;
      while (znac) {
        write(std, "0", 1);
        znac--;
      }
    }
  }
  write(std, &buffer[counter], SIZE_BUFFER - counter);
  return counter;
}
/*---------------------------------------------------------------------------*/
int swriteInt(char* buff, int num, int radix, int znac)
{
  
  char sign = '-';
  int i = 0;
  int j = 0;
  int k = 0;
  char buffer[SIZE_BUFFER];
  int counter = SIZE_BUFFER;


  if (num == 0) {
    buff[0] = '0';
    return 1;
  }

  if (radix == 10) {
    if (num < 0) {
      buff[0] = sign;
      num = -num;
    }
  }

  while (num) {
    if (num % radix > 9) {
      buffer[--counter] = 'A' + num % radix - 10;
      num /= radix;
    } else {
      buffer[--counter] = '0' + (num % radix);
      num /= radix;
    }
  }
  if (znac > -1) {
    if ((SIZE_BUFFER - counter) < znac) {
      znac = znac - SIZE_BUFFER + counter;
      while (znac) { 
        buff[i] = '0';
        i++;
        j++;
        znac--;
      }
    }
  }
  
  while(i < SIZE_BUFFER - counter + j) {
    buff[i] = buffer[counter + k++];
    i++;
  }

  return counter;
}

