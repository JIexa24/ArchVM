#include "../include/term.h"

int main() {
  int rows;
  int cols;
  
  mt_clrscr();
  mt_gotoXY(10,11); 

  write(1,"pozition 10:11",14);

  mt_setfgcolor(clr_blue);
  write(1,"blueText",8);
  mt_getscreensize(&rows, &cols);
  mt_gotoXY(0,0);
  writeInt(1, rows, 10, -1);
  write(1," ",1);
  writeInt(1, cols, 10, -1);

  mt_setfgcolor(clr_red);

  writeInt(1, rows, 10, -1);
  write(1," ",1);
  writeInt(1, cols, 10, -1);

  mt_setbgcolor(clr_blue);
  writeInt(1, rows, 10, -1);
  write(1," ",1);
  writeInt(1, cols, 10, -1);


  int ret = mt_gotoXY(-5, 1);
  if (ret == -1) {
    write(1,"\nmt_gotoXY error\n",17);
  } else { 
    write(1,"pozition -5:10", 14);
  }

  if (mt_setfgcolor(100) != -1) {
    write(1,"mt_setfgcolor error\n",20);
  }
  if (mt_setbgcolor(100) != -1) {
    write(1,"mt_setfgcolor error\n",20);
  }
  return 0;
}
