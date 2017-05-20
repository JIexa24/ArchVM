/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/term.h"

int mt_clrscr()
{
  writeChar(1, "\E[H\E[2J");
  return 0;
}
/*---------------------------------------------------------------------------*/
int mt_gotoXY(int x, int y)
{
  int rows = 0;
  int cols = 0;
  mt_getscreensize(&rows, &cols);
  if (((y < rows) & (y >= 0)) & ((x < cols) & (x >= 0))) {
    writeChar(1, "\E[");
    writeInt(1, y, 10, -1);
    writeChar(1, ";");
    writeInt(1, x, 10, -1);
    writeChar(1, "H");
    return 0;
  } else {
    return -1;
  }
}
/*---------------------------------------------------------------------------*/
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
/*---------------------------------------------------------------------------*/
int mt_setfgcolor(enum colors color)
{
  if (color >= 0 & color <= 9) {
    writeChar(1, "\E[");
    writeInt(1, 30 + color, 10, -1);
    writeChar(1, "m");
    return 0;
  } else {
    return -1;
  }
}
/*---------------------------------------------------------------------------*/
int mt_setbgcolor(enum colors color)
{
  if (color >= 0 & color <= 9) {
    writeChar(1, "\E[");
    writeInt(1, 40 + color, 10, -1);
    writeChar(1, "m");
    return 0;
  } else {
    return -1;
  }
}
