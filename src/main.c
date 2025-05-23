#include <stdio.h>
#include "filehandling.h"
#include "terminal.h"
#include <termios.h>

void print_intended_usage() {
    printf("Intended usage of spirit: spirit + flags + <..files>\n");
}

int main(int argc, char **argv) {
    if (argc == 1) {
        // The below function is temporarily commented out. Due to the nature
        // of the makefile, it prints every time the makefile is ran.
        // Once filehandling is implemented, this will be uncommented.
        //print_intended_usage();
        //exit(1);
    }
    int i = set_terminal_attributes();
    /// Clears the screen
    write(STDOUT_FILENO, "\x1b[2J]", 4);
    /// Moves the cursor to the top left
    write(STDOUT_FILENO, "\x1b[H", 3);

    // b moves it down and c moves it over
    //write(STDOUT_FILENO, "\x1b[1C\x1b[2B", 8);
    get_winsize();
    int err = movement_loop();
    if (err) {
        fprintf(stderr, "movement loop exited with non-zero exit status");
        exit(err);
    }
    return 0;
}
