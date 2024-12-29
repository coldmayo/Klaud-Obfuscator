#include <stdio.h>
#include <stdlib.h>
#include "obfuscate.h"

int main() {
	system("gcc -S test.c");

	obfuscate("test.s");

	system("gcc -c test.s -o test.o");
	system("gcc test.o -o test");

	printf("Done\n");
}
