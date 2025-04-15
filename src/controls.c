#include "controls.h"

/// This function will handle the processing for any codes the text 
/// editor needs to read. Right now, it's incredibly primitive,
/// and will scale with time.
int process_escape_codes(char c, bool isNormalMode) {
    if (!isNormalMode) {
        fprintf(stderr, "process_escape_codes() was called OUT OF NORMAL MODE! exiting.");
        exit(1);
    }
    switch (c) {
        case CTRL_Q:
            exit(0);
            break; // unreachable code
        case LEFT:
            write(STDOUT_FILENO, "\x1b[1D", 4);
            return 0;
            break;
        case DOWN:
            write(STDOUT_FILENO, "\x1b[1B", 4);
            return 0;
            break;
        case UP:
            write(STDOUT_FILENO, "\x1b[1A", 4);
            return 0;
            break;
        case RIGHT:
            write(STDOUT_FILENO, "\x1b[1C", 4);
            return 0;
            break;
    }
    return -1;
}

/*
int move_cursor(int input) {
    switch (input) {
        case 2: //left
            break;
        case 3: //down  
            break;
        case 4: //up  
            break;
        case 5: //right    
            break;
    }
}
*/
