#ifndef READ_KEY_H
#define READ_KEY_H

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
/*

    tcflag_t c_iflag;      // режимы ввода 
    tcflag_t c_oflag;      // режимы вывода 
    tcflag_t c_cflag;      // режимы управления 
    tcflag_t c_lflag;      // режимы локали 
    cc_t c_cc[NCCS];       // управляющие символы

c_iflag - флаги констант:

*/
enum keys {
  KEY_l,
  KEY_s,
  KEY_r,
  KEY_t,
  KEY_i,
  KEY_q,
  KEY_f5,
  KEY_f6,
  KEY_up,
  KEY_down,
  KEY_left,
  KEY_right,
  KEY_enter,
  KEY_other
};

int rk_readkey(enum keys *key);
int rk_mytermsave(void);
int rk_mytermrestore(void);
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);

#endif
