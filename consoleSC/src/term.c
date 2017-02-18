#include "./../include/term.h"

/*
infocmp

enum colors {
	clr_black,
	clr_red,
	clr_green,
	clr_brown,
	clr_blue,
	clr_magenta,
	clr_cyan,
	clr_light_blue,
	clr_white,
	clr_default
};*/

int mt_clrscr()
{
  printf("\E[H\E[2J");
  return 0;
}
/*------------------------------------------------------------------------------*/
int mt_gotoXY(int x, int y)
{
  int rows, cols;

  mt_getscreensize(&rows, &cols);
  if (((y < rows) && (y >= 0)) && ((x < cols) && (x >= 0))) {
    printf("\E[%d;%dH", y, x);
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
    printf("\E[%dm", 30 + color);
    return 0;
  } else {
    return -1;
  }
}
/*------------------------------------------------------------------------------*/
int mt_setbgcolor(enum colors color)
{
  if (color >= 0 && color <= 9) {
    printf("\E[%dm", 40 + color);
    return 0;
  } else {
    return -1;
  }
}
