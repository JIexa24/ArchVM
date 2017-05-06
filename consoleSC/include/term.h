/*
  Created by JIexa24 (Alexey R.)
*/
#ifndef CONSOLE_SC_H
#define CONSOLE_SC_H

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "./../../print/include/write.h"

enum colors {
	clr_black      = 0,
	clr_red        = 1,
	clr_green      = 2,
	clr_yellow     = 3,
	clr_blue       = 4,
	clr_purple     = 5,
	clr_cyan       = 6,
	clr_light_blue = 7,
	clr_default    = 9
};

int mt_clrscr();
int mt_gotoXY(int x, int y);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(enum colors color);
int mt_setbgcolor(enum colors color);

#endif
