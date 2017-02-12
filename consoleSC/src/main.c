#include "../include/term.h"

int main() {
  int rows;
  int cols;

  mt_clrscr();
  mt_gotoXY(10,11);
  printf("pozition 10:11");

  mt_setfgcolor(clr_blue);
  printf(" blueText");
  mt_getscreensize(&rows, &cols);
  mt_gotoXY(0,0);
  mt_setfgcolor(clr_red);
  mt_setbgcolor(clr_blue);
  printf("%d %d", rows, cols);
  int ret = mt_gotoXY(-5, 1);
  if (ret == -1) {
    printf("\nmt_gotoXY error\n");
  } else { 
    printf("pozition -5:10");
  }

  if (mt_setfgcolor(100) != -1) {
    printf("mt_setfgcolor error\n");
  }
  if (mt_setbgcolor(100) != -1) {
    printf("mt_setfgcolor error\n");
  }
  return 0;
}
