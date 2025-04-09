#include "filehandling.h"

/*
* TODO: Need to write the buffer to a file. Also need to put the terminal in raw mode
* so that when the file gets written to you can go back and edit the previous
* lines.
*/


/// Will hold all the special escape codes for the program to read.
enum EscapeCodes {
    CTRL_Q = 17,
    LEFT = 104,
    DOWN = 106,
    UP = 107,
    RIGHT = 108
};

/// This function will handle the processing for any codes the text 
/// editor needs to read. Right now, it's incredibly primitive,
/// and will scale with time.
int process_escape_codes(char c) {
    switch (c) {
        case CTRL_Q:
            return 1;
            break;
        case LEFT:
            return 2;
            break;
        case DOWN:
            return 3;
            break;
        case UP:
            return 4;
            break;
        case RIGHT:
            return 5;
            break;
    }
    return 0;
}

int move_cursor(int input) {
    switch (input) {
        case 2: //left
            write(STDOUT_FILENO, "\x1b[1D", 4);
            break;
        case 3: //down  
            write(STDOUT_FILENO, "\x1b[1B", 4);
            break;
        case 4: //up  
            write(STDOUT_FILENO, "\x1b[1A", 4);
            break;
        case 5: //right    
            write(STDOUT_FILENO, "\x1b[1C", 4);
            break;
    }
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
    char buff = '\0';
    while(1) {
        read(STDIN_FILENO, &buff, 1);
        if (input_vector.size == input_vector.capacity) {
            int res = resize_char_vector(&input_vector);
            if (res != 0) {
                fprintf(stderr, "ERROR: Failed to realloc a larger array capacity.");
                break;
            }
        }
        int d = process_escape_codes(buff);
        if (d == 1) {
            break;
        }
        if (d >= 2 && d <= 5) {
            move_cursor(d);
        }
        if (buff != '\0') {
            write(STDOUT_FILENO, "\x1b[1D", 4);
            input_vector.char_array[input_vector.size] = buff;
            input_vector.size += 1;
            input_vector.char_array[input_vector.size] = '\0';
            buff = '\0';
        }
    }
    //fclose(file);
    printf("%s\r\n", input_vector.char_array);
    free(input_vector.char_array);
    input_vector.char_array = NULL;
    return 0;
}
