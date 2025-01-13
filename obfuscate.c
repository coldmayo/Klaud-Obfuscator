#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <dirent.h>
#include "includes/utils.h"

// take into account for the files and functions used in by the obfuscator
typedef struct {
	char ** file_names;
	int count;
    int curr_func;
} Used;

// finding the number associated with .LFB* and .LFE* for the main function
int find_main_num(char * code) {
    int i = 0;
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
    return func_num;
}

// find out if the file is to be ignored by the function picker
bool ignore(const char* file_name, Used * used) {
	for (int i = 0; i < used->count; i++) {
        if (strcmp(file_name, used->file_names[i]) == 0) {
            return true;
        }
    }
    return false;
}

// adds a file to the ignore list, if used already it will be ignored
void add_ignore_list(const char * file_name, Used * used) {
	used->file_names = realloc(used->file_names, sizeof(char*) * (used->count + 1));
	used->file_names[used->count] = strdup(file_name);
	used->count++;
}

// randomly chooses a "snippet" file that contains a nonsensical function to use as a function
char * choose_func_file(Used * used) {
    struct dirent* entry;
    char ** file_names = malloc(sizeof(char *)*1024);
    if (!file_names) return NULL;

    DIR* dir = opendir("./snippets/");
    if (!dir) {
        free(file_names);
        return NULL;
    }

    int file_count = 0;
    while ((entry = readdir(dir)) != NULL && file_count < 1024) {
        if (entry->d_type == DT_REG && !ignore(entry->d_name, used)) {
            file_names[file_count] = strdup(entry->d_name);
            if (file_names[file_count] == NULL) {
                perror("Memory allocation failed");
                closedir(dir);
                for (int i = 0; i < file_count; i++) {
                    free(file_names[i]);
                }
                free(file_names);
                return NULL;
            }
            file_count++;
        }
    }

    closedir(dir);
    if (file_count == 0) {
        free(file_names);
        return strdup("");
    }

	char* selected_file;
    int random_index = rand() % (file_count + 1);
    if (random_index < file_count) {
        selected_file = strdup(file_names[random_index]);
        if (selected_file) {
            add_ignore_list(selected_file, used);
        }
    } else {
        selected_file = strdup("pingus");
    }

    // Freeing
    for (int i = 0; i < file_count; i++) {
        free(file_names[i]);
    }
    free(file_names);

    return selected_file;
}

// shows the number of functions in the assembly
int num_o_func(char * code) {
    int i = 0;
	int num_func = 0;

	while (code[i] != '\0') {
		if (code[i] == 'B' && code[i-1] == 'F' && code[i-2] == 'L' && code[i-3]=='.' && i>= 3) {
			num_func++;
		}
		i++;
	}
	return num_func;
}

// creates a function to insert into the assembly code
char * gen_func(char * file_name, char * code, Used * used, char * func) {
    
	char str[70] = ".file\t\"%s\"\n\t.text\n";
	char result[40000];
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
        "\t.size\tf__%d, .-f__%d\n";
	
	if (func != NULL && func[0] != '\0') {
		strcpy(func_template, func);
	}

	int num_func = num_o_func(code);
    used->curr_func = num_func;

	sprintf(result, func_template, file_name, num_func, num_func, num_func, num_func, num_func, num_func, num_func);
	sprintf(str, str, file_name);
	remove_substring(code, str);
	strcat(result, code);
	char * ret = malloc(strlen(result)+1);
	strcpy(ret, result);
	return ret;
}

// generates a function that calls a bunch of empty functions
char * dead_link(char * file_name, char * code, Used * used) {
    
	int main_num = find_main_num(code);
	char temp[20000];
    char main_temp[20000] =
    	".text\n"
        "\t.globl\tf__%%d\n"
        "\t.type\tf__%%d, @function\n"
        "f__%%d:\n"
        ".LFB%%d:\n"
        "\t.cfi_startproc\n"
        "\tpushq\t%rbp\n"
        "\t.cfi_def_cfa_offset 16\n"
        "\t.cfi_offset 6, -16\n"
        "\tmovq\t%rsp, %rbp\n"
        "\t.cfi_def_cfa_register 6\n"
        "%s\n"
        "\tmovl\t$0, %%%%eax\n"
        "\tpopq\t%rbp\n"
        "\t.cfi_def_cfa 7, 8\n"
        "\tret\n"
        "\t.cfi_endproc\n"
        ".LFE%%d:\n"
        "\t.size\tf__%%d, .-f__%%d\n";
    
    strcpy(main_temp, temp);
    int i;
    // add extra function calls
	int before = rand() % (5+1);
	char base[25] = "\tcall\tf__%d\n";
	char buffer[25];
	char start[200] = {0}; char end[200] = {0};
	i = 0;
	char f[50];
	int random;
	strcpy(f, file_name);
	f[strlen(f)-1] = 'c';
	while (i < before) {
        code = gen_func(file_name, code, used, "\0");
        random = rand()%(num_o_func(code)+ 1)+2;
        while (random == main_num) {
			random = rand()%(num_o_func(code)+ 1)+2;
        }
		sprintf(buffer, base, random);
		strcat(start, buffer);
		i++;
	}
	sprintf(temp, main_temp, start, end);	
	int num_func = num_o_func(code);
	sprintf(temp, main_temp, num_func, num_func, num_func, num_func, num_func, num_func, num_func);
	strcpy(main_temp, temp);
    strcat(main_temp, code);
    char * ret = malloc(strlen(main_temp)+1);
	strcpy(ret, main_temp);
	return ret;
}

char * choose_func(char * file_name, char * code, Used * used) {
    char * res = choose_func_file(used);
	char * func;
	char file[70] = "./snippets/";
	if (strcmp("\0", res) == 0) {
		code = gen_func(file_name, code, used, "\0");
	} else if (strcmp("pingus", res) == 0) {
        code = dead_link(file_name, code, used);
    } else {
    	strcat(file, res);
		func = read_file(file);
		code = gen_func(file_name, code, used, func);
	}
	return code;
}

char *main_link(char * file_name, char *code, Used * used) {

    int i = 0;

	char new_hidden_func[10000] = {0};

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

    int func_num = find_main_num(code);
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
	int random;
	while (i < before) {
		code = choose_func(f, code, used);
        random = used->curr_func;
		sprintf(buffer, base, random);
		strcat(start, buffer);
		i++;
	}
	while (i < after+before) {
		code = choose_func(f, code, used);
        random = used->curr_func;
		sprintf(buffer, base, random);
		strcat(end, buffer);
		i++;
	}
	i = 0;
	sprintf(temp, main_temp, start, end);
	strcpy(main_temp, temp);
	int hidden_num = num_o_func(code);

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

    // track parsing state
    bool in_main = false;
    bool copying_main = false;

    // Buffers for the modified code
    char updated_code[20000] = {0};
    strcat(updated_code, code);
	
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
	char *ret = malloc(strlen(updated_code) + 1);
    strcpy(ret, updated_code);
    return ret;
}


int obfuscate_asm(char * file, int layers) {
	Used used = {NULL, 0, 0};
	char * code = read_file(file);
	int i = 0;
	while (i < layers) {
		code = main_link(file, code, &used);
		i++;
	}

	printf("%s\n", code);
	code[strlen(code)] = '\n';
	write_file(file, code);
	free(code);
	return 0;
}
