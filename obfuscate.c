#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * read_file(char * file) {
	FILE * f;

	f = fopen(file, "rb");
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	rewind(f);
	char * str = malloc(size+1);
	size_t read_sz = fread(str, 1, size, f);
	str[size] = '\0';
	
	//printf("%s", str);
	return str;
}

void write_file(char * file, char * contents) {
	FILE * f;
	f = fopen(file, "w");

	fputs(contents, f);

	fclose(f);
}

int num_digits(int num) {
	if (num == 0) {
		return 1;
	}

	int i = 0;

	while (num != 0) {
		num = num/10;
		i++;
	}
	return i;
}

void remove_substring(char * str, const char * substr) {
	char *pos = strstr(str, substr);  // Find the substring
    if (pos != NULL) {
        size_t len = strlen(substr);  // Length of the substring
        // Shift characters forward
        memmove(pos, pos + len, strlen(pos + len) + 1);
    }
}

char * gen_func(char * code) {
	char func_template[2000] =
        ".file\t\"test.c\"\n"
        "\t.text\n"
        "\t.globl\tf___\n"
        "\t.type\tf___, @function\n"
        "f___:\n"
        ".LFB*:\n"
        "\t.cfi_startproc\n"
        "\tpushq\t%rbp\n"
        "\t.cfi_def_cfa_offset 16\n"
        "\t.cfi_offset 6, -16\n"
        "\tmovq\t%rsp, %rbp\n"
        "\t.cfi_def_cfa_register 6\n"
        "\tmovl\t$0, %eax\n"
        "\tpopq\t%rbp\n"
        "\t.cfi_def_cfa 7, 8\n"
        "\tret\n"
        "\t.cfi_endproc\n"
        ".LFE*:\n"
        "\t.size\tf___, .-f___\n";
        

	// find number of functions

	int i = 0;
	int num_func = 0;
	
	while (code[i] != '\0') {
    	//printf("%c", code[i]);
		if (code[i] == 'B' && code[i-1] == 'F' && code[i-2] == 'L' && code[i-3]=='.' && i>= 3) {
			num_func++;
		}
		i++;
	}

	// add num_func
	i = 0;
	int skip = 0;
	while (func_template[i] != '\0') {
		if (func_template[i] == '_' && func_template[i-1] == '_' && func_template[i-2] == '_' && i>= 4) {
			func_template[i] = '0'+num_func;
		} else if (func_template[i] == '*' && i>= 4) {
			func_template[i] = '0'+num_func;
			//func_template[i+1] = ' ';
			//func_template[i+2] = ' ';
		}
		i++;
	}

	// stick template onto the code

	remove_substring(code, ".file\t\"test.c\"\n\t.text\n");
	strcat(func_template, code);
	//printf("%s\n", func_template);
	char * ret = malloc(strlen(func_template)+1);
	strcpy(ret, func_template);
	return ret;
}

int obfuscate(char * file) {

	char * code = read_file(file);

	code = gen_func(code);

	write_file(file, code);

	return 0;
}
