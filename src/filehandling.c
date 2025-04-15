#include "filehandling.h"

/*
* TODO: Need to write the buffer to a file. Also need to put the terminal in raw mode
* so that when the file gets written to you can go back and edit the previous
* lines.
*/

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

// I should really REALLY fix the way these functions handle this.
// why am i doing all this TS stuff? its because I may add visual mode too :) 
// its more extensible this way because then I just 
// add another thing everywhere
int movement_loop() {
    Terminal_Status TS = {.isNormalMode = true, .isInsertMode = false};
    char c = '\0';
    for(;;) {
        read(STDIN_FILENO, &c, 1);
        process_escape_codes(c, true);
        if (c == 'i') {
            enable_echoing();
            TS.isInsertMode = true;
            TS.isNormalMode = false;
            read_text_input(&TS);
        }
        c = '\0';
    }
    return 0;
}


// Returns an error code, hence the int return
// This function does too much.
/// This is the primary loop that reads raw text from the terminal.
/// All it does right now is reads characters, stores them, and then
/// prints them to the terminal when CTRL_Q is pressed.
int read_text_input(Terminal_Status *TS) {
    CharVector input_vector = init_char_vector(); 
    char buff = '\0';
    for(;;) {
        read(STDIN_FILENO, &buff, 1);
        if (buff == ESC) {
            disable_echoing();
            TS->isNormalMode = true;
            TS->isInsertMode = false;
            break;
        }
        if (input_vector.size == input_vector.capacity) {
            int res = resize_char_vector(&input_vector);
            if (res != 0) {
                fprintf(stderr, "ERROR: Failed to realloc a larger array capacity.");
                break;
            }
        }
        if (buff != '\0') {
            //write(STDOUT_FILENO, "\x1b[1C", 4);
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
