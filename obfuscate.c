#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "includes/utils.h"

int num_o_func(char * code) {
    int i = 0;
	int num_func = 0;

	while (code[i] != '\0') {
    	//printf("%c", code[i]);
		if (code[i] == 'B' && code[i-1] == 'F' && code[i-2] == 'L' && code[i-3]=='.' && i>= 3) {
			num_func++;
		}
		i++;
	}
	return num_func;
}

char * gen_func(char * file_name, char * code, char * func) {
	char str[70] = ".file\t\"%s\"\n\t.text\n";
	char result[20000];
	char func_template[2000] =
        ".file\t\"%s\"\n"
        "\t.text\n"
        "\t.globl\tf__%d\n"
        "\t.type\tf__%d, @function\n"
        "f__%d:\n"
        ".LFB%d:\n"
        "\t.cfi_startproc\n"
        "\tpushq\t%rbp\n"
        "\t.cfi_def_cfa_offset 16\n"
        "\t.cfi_offset 6, -16\n"
        "\tmovq\t%rsp, %rbp\n"
        "\t.cfi_def_cfa_register 6\n"
        "\tmovl\t$0, %%eax\n"
        "\tpopq\t%rbp\n"
        "\t.cfi_def_cfa 7, 8\n"
        "\tret\n"
        "\t.cfi_endproc\n"
        ".LFE%d:\n"
        "\t.size\tf__%d, .-f__%d \n";
	//printf("%s\n", file_name);
	//sprintf(result, func_template, file_name);
	//printf("%s\n", result);
	//strcpy(func_template, result);
	if (func != NULL && func[0] != '\0') {
		strcpy(func_template, func);
	}
	// find number of functions

    int num_func = num_o_func(code);

	// add num_func
	
	sprintf(result, func_template, file_name, num_func, num_func, num_func, num_func, num_func, num_func, num_func);
	// stick template onto the code
	sprintf(str, str, file_name);
	remove_substring(code, str);
	//printf("%s\n", result);
	strcat(result, code);
	//printf("%s\n", result);
	char * ret = malloc(strlen(result)+1);
	strcpy(ret, result);
	return ret;
}

// goal of this function is to take the main function and put it into a hidden function

char *main_link(char * file_name, char *code) {
    int i = 0;

    // Buffer for the new hidden function
    char new_hidden_func[10000] = {0};

    // Dynamically create unique labels
    
    
    i = 0;

    // Templates for function headers and footers with dynamic labels
	char temp[2000];
    char main_temp[2000] =
    	".text\n"
        "\t.globl\tmain\n"
        "\t.type\tmain, @function\n"
        "main:\n"
        ".LFB%d:\n"
        "\t.cfi_startproc\n"
        "\tpushq\t%rbp\n"
        "\t.cfi_def_cfa_offset 16\n"
        "\t.cfi_offset 6, -16\n"
        "\tmovq\t%rsp, %rbp\n"
        "\t.cfi_def_cfa_register 6\n"
        "%%s"
        "\tcall\tf__%%%%d\n"
		"%%s"
        "\tmovl\t$0, %%%%%%%%eax\n"
        "\tpopq\t%rbp\n"
        "\t.cfi_def_cfa 7, 8\n"
        "\tret\n"
        "\t.cfi_endproc\n"
        ".LFE%d:\n"
        "\t.size\tmain, .-main\n"
        "\t.ident\t\"GCC: (GNU) 14.2.1 20240910\"\n"
        "\t.section\t.note.GNU-stack,\"\",@progbits";
// Find main function label #
    int j = 0;
    int func_num = 1;
    char num[6];
    while (code[i] != '\0') {
		if (code[i] == 'm' && code[i+1] == 'a' && code[i+2] == 'i' && code[i+4] == ':') {
			while (code[i+10+j] != ':') {
				num[j] = code[i+10+j]+'0';
				j++;
			}
			break;
		}
		i++;
    }
    num[j] = '\0';
    sscanf(num, "%d", &func_num);
    sprintf(temp, main_temp, func_num, func_num);
    strcpy(main_temp, temp);
    // add extra function calls
	int before = rand() % (5+1);
	int after = rand() % (5+1);
	char base[25] = "\tcall\tf__%d\n";
	char buffer[25];
	char start[200] = {0}; char end[200] = {0};
	i = 0;
	char f[50];
	strcpy(f, file_name);
	f[strlen(f)-1] = 'c';
	while (i < before) {
		code = gen_func(f, code, "\0");
		sprintf(buffer, base, rand()%(i+ 1)+2);
		strcat(start, buffer);
		i++;
	}
	while (i < after+before) {
		code = gen_func(f, code, "\0");
		sprintf(buffer, base, rand()%(i+ 1)+2);
		strcat(end, buffer);
		i++;
	}
	i = 0;
	sprintf(temp, main_temp, start, end);
	strcpy(main_temp, temp);
	int hidden_num = num_o_func(code);
	//printf("%d\n%d\n____\n", hidden_num, num_o_func(code));
	sprintf(temp, main_temp, hidden_num);
	strcpy(main_temp, temp);
    char hidden_header[200];
	int unique_label_id = num_o_func(code);
	
	snprintf(hidden_header, sizeof(hidden_header),
        "\t.text\n"
        "\t.globl\tf__%d\n"
        "\t.type\tf__%d, @function\n"
        "f__%d:\n"
        ".LFB%d:\n",
        hidden_num, hidden_num, hidden_num, unique_label_id);

    char hidden_footer[200];
    snprintf(hidden_footer, sizeof(hidden_footer),
        "\t.cfi_endproc\n"
        ".LFE%d:\n"
        "\t.size\tf__%d, .-f__%d\n",
        unique_label_id, hidden_num, hidden_num);

    // Copy the hidden header to the new function buffer
    strcat(new_hidden_func, hidden_header);

    // Flags to track parsing state
    bool in_main = false;
    bool copying_main = false;

    // Buffers for the modified code
    char updated_code[20000] = {0};
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

    // Add the new hidden function to the end of the updated code
    //strcat(new_hidden_func, updated_code);
    char * tmp = strdup(updated_code);
    strcpy(updated_code, new_hidden_func);
    strcat(updated_code, tmp);
    free(tmp);
	// edit the main function
	i = 0;
	while (updated_code[i] != '\0') {
		if (updated_code[i+14] == 'm' && updated_code[i+15] == 'a') {
			updated_code[i] = '\0';
			break;
		}
		i++;
	}
	
	strcat(updated_code, main_temp);
    // Allocate memory for the return string
    char *ret = malloc(strlen(updated_code) + 1);
    strcpy(ret, updated_code);
    return ret;
}


int obfuscate_asm(char * file, int layers) {
	char * code = read_file(file);
	int i = 0;
	while (i < layers) {
		code = main_link(file, code);
		i++;
	}

	printf("%s\n", code);
	code[strlen(code)] = '\n';
	write_file(file, code);
	free(code);
	//printf("%s", code);
	return 0;
}
