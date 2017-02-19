#include "./../include/sc_register.h"
#include "./../include/sc_command.h"
#include "./../include/sc_memory.h"

extern int localRAM[];
extern short int sc_register;

extern int correctCommands[];

int main()
{
  int mem1 = 0, mem2 = 0;
  int bit1 = 0, bit2 = 0;
  int comm1 = 0, comm2 = 0;
  int command, operand;
  int ret;

  sc_memoryInit();
  sc_memorySet(3, 0x123);
  sc_memoryGet(1, &mem1);
  sc_memoryGet(3, &mem2);

  write(1, "0 = ", 4);
  writeInt(1, mem1, 16, -1);
  write(1, "\n", 1);

  write(1, "123 = ", 6);
  writeInt(1, mem2, 16, -1);
  write(1, "\n", 1);

  sc_memorySave("memory");

  /* Меняем ячейку памяти, загружаем память в неизмененном состоянии */
  sc_memorySet(3, 1);
  sc_memoryLoad("memory");
  sc_memoryGet(3, &mem1);

  write(1, "123 = ", 6);
  writeInt(1, mem1, 16, -1);
  write(1, "\n", 1);

  /* Проверка функций работы с регистром флагов */
  sc_regInit();
  sc_regSet(FLAG_DIVISION, 1);
  sc_regSet(FLAG_INTERRUPT, 1);

  write(1, "Flag register is ", 17);
  writeInt(1, sc_register, 16, -1);
  write(1, "\n", 1);

  sc_regGet(FLAG_DIVISION, &bit1);
  sc_regSet(FLAG_DIVISION, 0);
  sc_regGet(FLAG_DIVISION, &bit2);

  write(1, "1 = ", 4);
  writeInt(1, bit1, 10, -1);
  write(1, "\n", 1);

  write(1, "0 = ", 4);
  writeInt(1, bit2, 10, -1);
  write(1, "\n", 1);

  /* Кодирование/декодирование комманд */
  ret = sc_commandEncode(0x21, 1, &comm1);
  write(1, "Encoded command is ", 19);
  writeInt(1, comm1, 16, -1);
  write(1, " Return value: ", 15);
  writeInt(1, ret, 10, -1);
  write(1, "\n", 1);

  ret = sc_commandEncode(0x4, 4, &comm2);
  write(1, "Encoded command is ", 19);
  writeInt(1, comm2, 16, -1);
  write(1, " Return value: ", 15);
  writeInt(1, ret, 10, -1);
  write(1, "\n", 1);

  ret = sc_commandDecode(0x1084, &command, &operand);
  write(1, "Command: ", 9);
  writeInt(1, command, 10, -1);
  write(1, " Operand: ", 10);
  writeInt(1, operand, 10, -1);
  write(1, " Return value: ", 15);
  writeInt(1, ret, 10, -1);
  write(1, "\n", 1);

  ret = sc_commandDecode(0xB84, &command, &operand);
  write(1, "Command: ", 9);
  writeInt(1, command, 10, -1);
  write(1, " Operand: ", 10);
  writeInt(1, operand, 10, -1);
  write(1, " Return value: ", 15);
  writeInt(1, ret, 10, -1);
  write(1, "\n", 1);

  return 0;
}
