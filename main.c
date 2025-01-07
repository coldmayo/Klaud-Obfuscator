#include <stdio.h>
#include <stdlib.h>
#include "includes/obfuscate.h"

int main() {
	system("gcc -S test.c");

	obfuscate_asm("test.s");

	system("gcc -c test.s -o test.o");

	system("gcc test.o -s -o test");

	printf("Done\nTesting...\n");

	system("./test");
}
