#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

char * gen_func(char * code, char * func) {
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
        

	if (func != NULL && func[0] != '\0') {
		strcpy(func_template, func);
	}
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

// goal of this function is to take the main function and put it into a hidden function

char *main_link(char *code) {
    int i = 0;

    // Buffer for the new hidden function
    char new_hidden_func[5000] = {0};

    // Dynamically create unique labels
    int num_func = 0;
    while (code[i] != '\0') {
        if (code[i] == 'B' && code[i - 1] == 'F' && code[i - 2] == 'L' && code[i - 3] == '.' && i >= 3) {
            num_func++;
        }
        i++;
    }
    int unique_label_id = num_func;
    i = 0;

    // Templates for function headers and footers with dynamic labels
    char hidden_header[200];
    snprintf(hidden_header, sizeof(hidden_header),
        "\t.text\n"
        "\t.globl\thidden\n"
        "\t.type\thidden, @function\n"
        "hidden:\n"
        ".LFB%d:\n",
        unique_label_id);

    char hidden_footer[200];
    snprintf(hidden_footer, sizeof(hidden_footer),
        "\t.cfi_endproc\n"
        ".LFE%d:\n"
        "\t.size\thidden, .-hidden\n",
        unique_label_id);

    // Copy the hidden header to the new function buffer
    strcat(new_hidden_func, hidden_header);

    // Flags to track parsing state
    bool in_main = false;
    bool copying_main = false;

    // Buffers for the modified code
    char updated_code[10000] = {0};
    strcat(updated_code, code); // Start with the original code

    while (code[i] != '\0') {
        // Detect the start of the main function
        if (!in_main && strncmp(&code[i], ".globl\tmain", 11) == 0) {
            in_main = true;
        }

        // Detect the function body of main
        if (in_main && !copying_main && strncmp(&code[i], ".LFB", 4) == 0) {
            copying_main = true;
            i += 4; // Skip the label
        }

        // Copy the instructions inside the main function
        if (copying_main) {
            // Stop copying at the end of the main function
            if (strncmp(&code[i], "ret", 3) == 0) {
                copying_main = false;
                in_main = false;

                // Add a return to the hidden function
                strcat(new_hidden_func, "\tret\n");
                break;
            }

            // Append the instruction to the hidden function
            strncat(new_hidden_func, &code[i], 1);
        }

        i++;
    }

    // Add the footer to the hidden function
    strcat(new_hidden_func, hidden_footer);

    // Insert a call to hidden in the main function
    char main_replacement[200];
    snprintf(main_replacement, sizeof(main_replacement),
        "\tcall\thidden\n");
    strcat(updated_code, main_replacement);

    // Add the new hidden function to the end of the updated code
    strcat(updated_code, new_hidden_func);

    // Allocate memory for the return string
    char *ret = malloc(strlen(updated_code) + 1);
    strcpy(ret, updated_code);
    return ret;
}


int obfuscate(char * file) {

	char * code = read_file(file);

	code = gen_func(code, "\0");

	code = gen_func(code, "\0");

	code = main_link(code);

	write_file(file, code);
	printf("%s", code);
	return 0;
}
