#include <stdio.h>
#include <unistd.h> //for read and stdin_fileno
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
* TODO: Need to write the buffer to a file. Also need to put the terminal in raw mode
* so that when the file gets written to you can go back and edit the previous
* lines.
*/

enum EscapeCodes {
    CTRL_Q = 17,
};

typedef struct {
    char *char_array;
    int size;
    int capacity;
} CharVector;

CharVector init_char_vector() {
    const int DEFAULT_CAPACITY = 10;
    void* array_block = malloc(DEFAULT_CAPACITY);
    char* default_array = (char *) memset(array_block, 0, DEFAULT_CAPACITY);
    CharVector vec = {default_array, 0, DEFAULT_CAPACITY};
    return vec;
}

/// Returns an error code, hence the int return
int resize_char_vector(CharVector *vec) {
    const int ARRAY_SIZE = vec->capacity*2;
    char* new_array = realloc(vec->char_array, ARRAY_SIZE);
    if (new_array == NULL) {
        return 1;
    }
    vec->capacity *= 2;
    memmove(new_array, vec->char_array, vec->size);
    //free(vec->char_array); // Might literally crash the program
    vec->char_array = new_array;
    return 0;
}

int process_escape_codes(char c) {
    if (c == CTRL_Q) {
        return 1;
    }
    return 0;
}

FILE* handle_file(char* file_path) { 
    FILE* file = fopen(file_path, "w"); 
    if (file == NULL) {
        fprintf(stderr, "ERROR: Error opening file.\n");
        exit(1); 
    }
    return file;
}

/// Returns an error code, hence the int return
/// This function does too much.
int read_text_input() {
    CharVector input_vector = init_char_vector(); 
    char buff;
    while(scanf(" %c", &buff) != EOF) {
        input_vector.size += 1;
        if (input_vector.size == input_vector.capacity) {
            int res = resize_char_vector(&input_vector);
            if (res != 0) {
                fprintf(stderr, "ERROR: Failed to realloc a larger array capacity.");
                break;
            }
        }
        if (process_escape_codes(buff) != 0) {
            break;
        }
        strcat(input_vector.char_array, &buff);
    }
    printf("%s", input_vector.char_array);
    //fclose(file);
    free(input_vector.char_array);
    input_vector.char_array = NULL;
    return 0;
}
