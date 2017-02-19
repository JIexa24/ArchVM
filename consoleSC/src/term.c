#include "./../include/term.h"

/*
infocmp

enum colors {
	clr_black,
	clr_red,
	clr_green,
	clr_yellow,
	clr_blue,
	clr_purple,
	clr_light_blue,
	clr_white,
	clr_default
};*/

int mt_clrscr()
{
  write(1, "\E[H\E[2J", 7);
  return 0;
}
/*------------------------------------------------------------------------------*/
int mt_gotoXY(int x, int y)
{
  int rows, cols;
  
  mt_getscreensize(&rows, &cols);
  if (((y < rows) && (y >= 0)) && ((x < cols) && (x >= 0))) {
    write(1, "\E[", 2);
    writeInt(1, y, 10, -1);
    write(1, ";", 1);
    writeInt(1, x, 10, -1);
    write(1, "H", 1);
    return 0;
  } else {
    return -1;
  }
}
/*------------------------------------------------------------------------------*/
int mt_getscreensize(int *rows, int *cols)
{
  struct winsize w;
  if (!ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)) {
    *rows = w.ws_row;
    *cols = w.ws_col;
    return 0;
  }  else {
    return -1;
  }
}
/*------------------------------------------------------------------------------*/
int mt_setfgcolor(enum colors color)
{
  if (color >= 0 && color <= 9) {
    write(1, "\E[", 2);
    writeInt(1, 30 + color, 10, -1);
    write(1, "m", 1);
    return 0;
  } else {
    return -1;
  }
}
/*------------------------------------------------------------------------------*/
int mt_setbgcolor(enum colors color)
{
  if (color >= 0 && color <= 9) {
    write(1, "\E[", 2);
    writeInt(1, 40 + color, 10, -1);
    write(1, "m", 1);
    return 0;
  } else {
    return -1;
  }
}
