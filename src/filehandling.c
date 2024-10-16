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


/// Will hold all the special escape codes for the program to read.
enum EscapeCodes {
    CTRL_Q = 17,
};

/// The struct for a resizable string. Similar to an ArrayList from Java.
typedef struct {
    char *char_array;
    int size;
    int capacity;
} CharVector;


/// Inits and returns a struct. Acts like a constructor for a class, almost.
CharVector init_char_vector(int size) {
    void* array_block = malloc(size);
    char* default_array = (char *) memset(array_block, 0, size);
    CharVector vec = {default_array, 0, size};
    return vec;
}

// Returns an error code, hence the int return
/// Whenever the CharVector is maxxed out, this function should be called 
/// to double its size.
int resize_char_vector(CharVector *vec) {
    const int ARRAY_SIZE = vec->capacity*2;
    char* new_array = realloc(vec->char_array, ARRAY_SIZE);
    if (new_array == NULL) {
        return 1;
    }
    // memmove(new_array, vec->char_array, vec->size);
    // free(vec->char_array); // Might literally crash the program (it does.)
    vec->char_array = new_array;
    vec->capacity = ARRAY_SIZE;
    return 0;
}

/// This function will handle the processing for any codes the text 
/// editor needs to read. Right now, it's incredibly primitive,
/// and will scale with time.
int process_escape_codes(char c) {
    if (c == CTRL_Q) {
        return 1;
    }
    return 0;
}

/// This function serves as a wrapper for handling errors with file opening.
/// Exits because a text editor can't edit nothing.
FILE* handle_file(char* file_path) { 
    FILE* file = fopen(file_path, "w"); 
    if (file == NULL) {
        fprintf(stderr, "ERROR: Error opening file.\n");
        exit(1); 
    }
    return file;
}

// Returns an error code, hence the int return
// This function does too much.
/// This is the primary loop that reads raw text from the terminal.
/// All it does right now is reads characters, stores them, and then
/// prints them to the terminal when CTRL_Q is pressed.
int read_text_input() {
    CharVector input_vector = init_char_vector(10);
    char buff;
    while(scanf("%c", &buff) != EOF) {
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
    printf("%s\n", input_vector.char_array);
    //fclose(file);
    free(input_vector.char_array);
    input_vector.char_array = NULL;
    return 0;
}
