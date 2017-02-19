#include "./../include/readkey.h"

void print_key(enum keys key)
{
  switch (key) {
    case KEY_l:
      write(1, "l\n", 2);
    break;
    case KEY_s:
      write(1, "s\n", 2);
    break;
    case KEY_r:
      write(1, "r\n", 2);
    break;
    case KEY_t:
      write(1, "t\n", 2);
    break;
    case KEY_i:
      write(1, "i\n", 2);
    break;
    case KEY_q:
      write(1, "q\n", 2);
    break;
    case KEY_up: 
      write(1, "up\n", 3);
    break;
    case KEY_down:
      write(1, "down\n", 5);
    break;
    case KEY_left:
      write(1, "left\n", 5);
    break;
    case KEY_right:
      write(1, "right\n", 6);
    break;
    case KEY_f5:
      write(1, "F5\n", 3);
    break;
    case KEY_f6: 
      write(1, "F6/n", 3);
    break;
	}
}

int main()
{
	struct termios options;
	enum keys key;
	char buf[100];
	
  rk_mytermsave();
  rk_mytermregime(0, 0, 1, 0, 1);
  write(1, "ECHO disabled\n", 14);

  read(STDIN_FILENO, &buf, 10);
  rk_mytermrestore();

  write(1, "Terminal settings restored\n", 27);

  read(STDIN_FILENO, &buf, 10);

  if (rk_mytermregime(0, 0, 0, 0, 2) == -1)
    write(1, "rk_mytermregime returned -1\n", 28);
  else
    write(1, "Wrong rk_mytermregime return value\n", 35);

  do {
    rk_readkey(&key);
    print_key(key);
  } while (key != KEY_q);

  return 0;
}
