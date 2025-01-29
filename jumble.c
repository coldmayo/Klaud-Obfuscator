// This code will change common assembly instructions and changes it to new ones which do the same thing
// The goal here is to confuse the decompiler

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "includes/utils.h"

char * chg_func_calls(char * code) {
	int i = 0;
	char half1[4000];
	char half2[4000];
	char real_func_call[100];
	char func_call[100];
	char func[60];
	bool func_fund = false;
	char buf[200];
	char * buff;
	int dest;
	int j;
	
	while (code[i] != '\0') {
		if (code[i+1] == 'c' && code[i+2] == 'a' && code[i+3] == 'l' && code[i+4] == 'l') {
			dest = i;
			strcpy(real_func_call, "call\t%s\n");
			strcpy(func_call, "\n\tlea\t%s(%rip), %rax\n\tcall\t*%rax\n");
			memset(func, 0, sizeof(func));
			func_fund = true;
			i += 6;
			j = 0;
		}
		if (func_fund == true) {
    		if (code[i] != '\t' && j < sizeof(func) - 1) {
				//printf("%c\n", code[i]);
				func[j] = code[i];
    		}
			
			j++;

			if (code[i+1] == '\n') {
				func_fund = false;
				//printf("%s", real_func_call);
				sprintf(buf, real_func_call, func);
				strcpy(real_func_call, buf);
				//printf("%s", buf);
				if (func[0] == 'f' && func[1] == '_') {
					dest = remove_substring(code, real_func_call);
				//printf("%s\n", real_func_call);
				//printf("%d %d\n", strlen(code), dest);
					if (dest != -1) {
						sprintf(buf, func_call, func);
						strcpy(func_call, buf);
					//printf("%s", func_call);
						insert_string(code, func_call, dest);
					}
				}
				
				
				//printf("%s\n\n", code);
				//printf("%s--\n", func);
			}
		}
		i++;
	}
	//printf("%s\n", code);
	return code;
}

int jumble_asm(char * file) {
	char * code = read_file(file);	
	code = chg_func_calls(code);
	printf("%s", code);
	write_file(file, code);
	free(code);
	return 0;
}
