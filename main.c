#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "includes/jumble.h"
#include "includes/obfuscate.h"

int main(int argc, char ** argv) {
	int layers = 0;
	char file_name[40];
	char asm_file[40];
	char ELF[40];
	char obj[40];
	char temp[40];
	char * buf;
	char buf2[50];
	char * commands[5] = {
		"gcc -S %s",
		"gcc -c %s -o %s",
		"gcc -no-pie %s -s -o %s",   // function names stripped here
		"./%s"
	};

	if (argc == 3) {
		strcpy(file_name, argv[1]);
		layers = strtol(argv[2], &buf, 10);
	} else if (argc < 2) {
		printf("You need to give a file name\n");
		return -1;
	}

	strcpy(temp, file_name);
	temp[strlen(temp)-1] = '\0';

	strcpy(ELF, temp);
	ELF[strlen(ELF)-1] = '\0';

	strcpy(asm_file, temp);
	asm_file[strlen(asm_file)] = 's';

	strcpy(obj, temp);
	obj[strlen(obj)] = 'o';
	
	sprintf(buf2, commands[0], file_name);
	printf("To assembly\n");
	system(buf2);

	obfuscate_asm(asm_file, layers);
	jumble_asm(asm_file);

	sprintf(buf2, commands[1], asm_file, obj);
	printf("Assembly to .o file\n");
	system(buf2);

	sprintf(buf2, commands[2], obj, ELF);
	printf(".o file to ELF/executable\n");
	system(buf2);

	printf("Done\nTesting...\n");
	sprintf(buf2, commands[3], ELF);
	system(buf2);
}
