/*
  Created by JIexa24 (Alexey R.)
*/
#include "./../include/asm.h"

int main(int argc, char *argv[])
{
	FILE *input, *output;

	if (argc != 3) {
		exit(1);
	}
	if (testArgv(argv) != 0) {
		exit(1);
	}
	if ((output = fopen(argv[1], "wb")) == NULL) {
		exit(1);
	}
	if ((input = fopen(argv[2], "rb")) == NULL) {
		exit(1);
	}
	

	fclose(input);
	fclose(output);
	return 0;
}
