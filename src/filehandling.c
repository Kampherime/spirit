#include "filehandling.h"

/*
* TODO: Need to write the buffer to a file. Also need to put the terminal in raw mode
* so that when the file gets written to you can go back and edit the previous
* lines.
*/


/// Will hold all the special escape codes for the program to read.
enum EscapeCodes {
    CTRL_Q = 17,
};

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
    CharVector input_vector = init_char_vector(); 
    char buff;
    while(1) {
        read(STDIN_FILENO, &buff, 1);
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
