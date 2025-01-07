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
	fclose(f);
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
	char *pos = strstr(str, substr);
    if (pos != NULL) {
        size_t len = strlen(substr);
        
        memmove(pos, pos + len, strlen(pos + len) + 1);
    }
}
void insert_string(char *destination, const char *source, int position) {
	int dest_len = strlen(destination);
    int source_len = strlen(source);

	memmove(destination + position + source_len, destination + position, dest_len - position + 1); // +1 to include the null terminator

	strncpy(destination + position, source, source_len);
}

void insert_char(char *destination, char c, int position) {
    int len = strlen(destination);

    // Move the part of the destination string to make room for the new character
    memmove(destination + position + 1, destination + position, len - position + 1); // +1 to include the null terminator

    // Insert the character into the destination string at the desired position
    destination[position] = c;
}
