/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/readkey.h"
/*

  tcflag_t c_iflag;      // режимы ввода 
  tcflag_t c_oflag;      // режимы вывода 
  tcflag_t c_cflag;      // режимы управления 
  tcflag_t c_lflag;      // режимы локали 
  cc_t c_cc[NCCS];       // управляющие символы

  c_iflag - флаги констант:
*/
int rk_readkey(enum keys *key)
{
  struct termios orig_options;
  char buf[16];
  int readNum;
/*---------------------------------------------------------------------------*/
/*
  tcgetattr(int fd, struct termios *termios_p) : получить параметры, 
  связанные с объектом, на который ссылается fd, и сохранить их в структуре
  termios, на которую ссылается termios_p. Эта функция может быть запущена из
  фонового процесса;однако, атрибуты терминала могут в дальнейшем изменяться
  основным процессом. 
*/
  if (tcgetattr(STDIN_FILENO, &orig_options) != 0) {
    return -1;
  }
  if (rk_mytermregime(0, 0, 1, 0, 1) != 0) {
    return -1;
  }
  readNum = read(STDIN_FILENO, buf, 15);

  if (readNum < 0) {
    return -1;
  }

  buf[readNum] = '\0';

  if (strcmp(buf, "l") == 0) { 
    *key = KEY_l;
  } else if (strcmp(buf, "s") == 0) {
    *key = KEY_s;
  } else if (strcmp(buf, "r") == 0) {
    *key = KEY_r;
  } else if (strcmp(buf, "t") == 0) {
    *key = KEY_t;
  } else if (strcmp(buf, "i") == 0) {
    *key = KEY_i;
  } else if (strcmp(buf, "q") == 0) {
    *key = KEY_q;
  } else if (strcmp(buf, "x") == 0) {
    *key = KEY_x;
  } else if (strcmp(buf, "d") == 0) {
    *key = KEY_d;
  } else if (strcmp(buf, "\n") == 0) {
    *key = KEY_enter;
  } else if (strcmp(buf, "\E[15~") == 0) { 
    *key = KEY_f5;
  } else if (strcmp(buf, "\E[17~") == 0) {
    *key = KEY_f6;
  } else if (strcmp(buf, "\E[A") == 0) {
    *key = KEY_up;
  } else if (strcmp(buf, "\E[B") == 0) {
    *key = KEY_down;
  } else if (strcmp(buf, "\E[C") == 0) {
    *key = KEY_right;
  } else if (strcmp(buf, "\E[D") == 0) {
    *key = KEY_left;
  } else if (strcmp(buf, "\E") == 0) {
    *key = KEY_esc;
  } else {
    *key = KEY_other;
  }
/*
  int tcsetattr(int fd, int optional_actions, struct termios *termios_p)
  меняет параметры, связанные с терминалом (если требуется поддержка 
  используемого оборудования, которая недоступна), и параметры структуры
  termios, связанной с termios_p. Для того, чтобы изменения вступили в силу,
  необходимо указать optional_actions:
*/
  if (tcsetattr(STDIN_FILENO, TCSANOW, &orig_options) != 0) {
    return -1;
  }

  return 0;
}
/*---------------------------------------------------------------------------*/
int rk_mytermsave(void)
{
  struct termios options;
  FILE *save;

  if (tcgetattr(STDIN_FILENO, &options) != 0) {
    return -1;
  }
  if ((save = fopen("termsettings", "wb")) == NULL) {
    return -1;
  }
  fwrite(&options, sizeof(options), 1, save);
  fclose(save);
	
  return 0;
}
/*---------------------------------------------------------------------------*/
int rk_mytermrestore(void)
{
  struct termios options;
  FILE *data;

  if ((data = fopen("termsettings", "rb")) == NULL) {
    return -1;
  } else {
    if (fread(&options, sizeof(options), 1, data) > 0) {
/*
  TCSAFLUSH
  изменения начинают работу после того, как на объект, на который указывает
  fd, были переданы все данные, предназначенные для вывода на запись; все 
  данные, которые были приняты (но не считаны), будут отменены перед тем, 
  как произошли изменения. 
*/
      if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &options) != 0) {
        fclose(data);
        return -1;
      } else {
        fclose(data);
        return -1;
      }
    }
    fclose(data);
  }

  return 0;
}
/*---------------------------------------------------------------------------*/
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint)
{
  struct termios options;
      
  if (tcgetattr(STDIN_FILENO, &options) != 0) {
    return -1;
  }
  if (regime == 1) {
    options.c_lflag |= ICANON;
  } else if (regime == 0) {
    options.c_lflag &= ~ICANON;
  } else {
    return -1;
  }
  if (regime == 0) {
    options.c_cc[VTIME] = vtime;
    options.c_cc[VMIN] = vmin;
    if (echo == 1) {
      options.c_lflag |= ECHO;
    } else if (echo == 0) {
      options.c_lflag &= ~ECHO;
    } else {
      return -1;
    }
    if (sigint == 1) {
      options.c_lflag |= ISIG;
    } else if (sigint == 0) {
      options.c_lflag &= ~ISIG;
    } else {
      return -1;
    }
  }
  if (tcsetattr(STDIN_FILENO, TCSANOW, &options) != 0) {
    return -1;
  }

  return 0;
}
