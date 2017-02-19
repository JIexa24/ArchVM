#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include "./../include/bc.h"

/*
char bigchar_0[64] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};
*/

char bigchar_plus[64] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0
};


char bigchar_0[64] = {
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 1, 0, 0, 0, 0, 1, 0,
  1, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 1,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 0, 1, 1, 1, 1, 0, 0
};

char bigchar_1[64] = {
  0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 1, 0, 1, 0,
  0, 0, 0, 1, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0
};

char bigchar_2[64] = {
  0, 0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 0, 0, 0, 1, 0,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0
};

char bigchar_3[64] = {
  0, 0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 1, 1, 1, 1, 1, 0
};

char bigchar_4[64] = {
  0, 0, 1, 0, 0, 0, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 0,
  0, 0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0
};

char bigchar_5[64] = {
  0, 0, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 1, 1, 1, 1, 1, 0
};

char bigchar_6[64] = {
  0, 0, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 0,
  0, 0, 1, 1, 1, 1, 1, 0
};

char bigchar_7[64] = {
  0, 0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0
};

char bigchar_8[64] = {
  0, 0, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 0,
  0, 0, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 0,
  0, 0, 1, 1, 1, 1, 1, 0
};

char bigchar_9[64] = {
  0, 0, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 0,
  0, 0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 1, 1, 1, 1, 1, 0
};

char bigchar_A[64] = {
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 1, 0, 0, 0, 0, 1, 0
};

char bigchar_B[64] = {
  0, 1, 1, 1, 1, 0, 0, 0,
  0, 1, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 1, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 0, 0,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 1, 1, 1, 1, 1, 0, 0
};

char bigchar_C[64] = {
  0, 0, 1, 1, 1, 1, 1, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 0
};

char bigchar_D[64] = {
  0, 1, 1, 1, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 1, 0, 0,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 1, 0, 0, 0, 0, 1, 0,
  0, 1, 0, 0, 0, 1, 0, 0,
  0, 1, 1, 1, 1, 0, 0, 0
};

char bigchar_E[64] = {
  0, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0
};

char bigchar_F[64] = {
  0, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0
};

int arrToBig(int *big, char *arr)
{
  int i;
  int x, y;

  for (i = 0; i < 64; i++) {
    x = i % 8;
    y = i / 8;
    bc_setbigcharpos(big, x, y, arr[i]);
  }
  return 0;
}

int main()
{
  int big[2], one[2], big_read[2];
  int testBuf[100];
  int bigAsci[256];
  int val1, val2;
  int ret1, ret2;
  int readen;  
  int fd, outAsci;
	
  mt_clrscr();

  arrToBig(big, bigchar_plus);
  arrToBig(one, bigchar_1);

  bc_box(2, 2, 78, 20);

  bc_printbigchar(big, 4, 4, clr_purple, clr_default);
  bc_printbigchar(one, 4, 12, clr_cyan, clr_default);

  arrToBig(big, bigchar_E);
  bc_printbigchar(big, 12, 4, clr_default, clr_red);

  bc_getbigcharpos(big, 3, 3, &val1);
  bc_getbigcharpos(big, 6, 1, &val2);

  mt_gotoXY(0, 21);
  
  write(1, "bc_getbigcharpos (3,3) 0=", 25);
  writeInt(1, val1, 10, -1);
  write(1, " (6, 1) 1=", 10);
  writeInt(1, val1, 10, -1);
  write(1, "\n", 1);

  if ((fd = open("bigtest", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR )) == -1) {
    write(2, "Open error\n", 11); 
    return -1;
  }
  if (bc_bigcharwrite(fd, big, 1) != 0) {
    write(2, "bc_bigcharwrite error!\n", 23); 
    return -1;
  }
  lseek(fd, 0, SEEK_SET);
  if (bc_bigcharread(fd, big_read, 1, &readen) != 0) {
    write(2, "bc_bigcharwrite error!\n", 23); 
    return -1;
  }
  if ((big[0] != big_read[0]) || (big[1] != big_read[1])) {
    write(2, "big != big_read\n", 16);
    return -1;
  }
  else
    write(1, "big == big_read\n", 16);

  /* Init of bigchars array */
  memset(bigAsci, 0, sizeof(int) * 256);
  arrToBig(bigAsci + ('+' * 2), bigchar_plus);
  arrToBig(bigAsci + ('0' * 2), bigchar_0);
  arrToBig(bigAsci + ('1' * 2), bigchar_1);
  arrToBig(bigAsci + ('2' * 2), bigchar_2);
  arrToBig(bigAsci + ('3' * 2), bigchar_3);
  arrToBig(bigAsci + ('4' * 2), bigchar_4);
  arrToBig(bigAsci + ('5' * 2), bigchar_5);
  arrToBig(bigAsci + ('6' * 2), bigchar_6);
  arrToBig(bigAsci + ('7' * 2), bigchar_7);
  arrToBig(bigAsci + ('8' * 2), bigchar_8);
  arrToBig(bigAsci + ('9' * 2), bigchar_9);
  arrToBig(bigAsci + ('A' * 2), bigchar_A);
  arrToBig(bigAsci + ('B' * 2), bigchar_B);
  arrToBig(bigAsci + ('C' * 2), bigchar_C);
  arrToBig(bigAsci + ('D' * 2), bigchar_D);
  arrToBig(bigAsci + ('E' * 2), bigchar_E);
  arrToBig(bigAsci + ('F' * 2), bigchar_F);
    if ((outAsci = open("bigchars", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR )) 
         == -1) {
    write(2, "Open error\n", 11); 
    return -1;
  }
  if (bc_bigcharwrite(outAsci, bigAsci, 128) != 0) {
    write(2, "bc_bigcharwrite error!\n", 23); 
    return -1;
  }
 
  /* Incorrect arguments */
  ret1 = bc_box(-1, 1, 8, 8);
  ret2 = bc_box(1, 10000, 10, 10);
  write(2, "bc_box returned 1:", 18);
  writeInt(2, ret1, 10, -1);
  write(2, " 2:", 3);
  writeInt(2, ret2, 10, -1);
  write(1, "\n", 1);

  ret1 = bc_printbigchar(big, 20000, 4, clr_red, clr_green);
  ret2 = bc_setbigcharpos(big, 10, 3, 1);
  writeInt(2, ret1, 10, -1);
  write(2, " bc_printbigchar returned ", 26);
  writeInt(2, ret2, 10, -1);
  write(1, "\n", 1);

  ret1 = bc_getbigcharpos(big, 3, 10, &val1);
  write(2, "bc_getbigcharpos returned ", 26);
  writeInt(2, ret1, 10, -1);
  write(1, "\n", 1);

  ret1 = bc_bigcharread(fd, testBuf, 8, &val2);
  ret2 = bc_bigcharwrite(-1, big, 1);
  write(2, "bc_bigcharread returned ", 24);
  writeInt(2, ret1, 10, -1);
  write(1, " bc_bigcharwrite returned ", 26);
  writeInt(2, ret2, 10, -1);
  write(1, "\n", 1);

  close(fd);
  close(outAsci);

  return 0;
}
