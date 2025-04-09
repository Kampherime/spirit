#include <stdio.h>
#include "./filehandling.c"
#include "./terminal.c"

/// A message that prints whenever the wrong amount of arguments are inputed.
void print_intended_usage() {
    printf("Intended usage of spirit: spirit + flags + <..files>\n");
}

///Serves as an entry point for the editor. Naturally, not all operations
///will be executed in this file.
int main(int argc, char **argv) {
    /*if (argc == 1) {
        // The below function is temporarily commented out. Due to the nature
        // of the makefile, it prints every time the makefile is ran.
        // Once filehandling is implemented, this will be uncommented.
        //print_intended_usage();
    }*/
    int i = set_terminal_attributes();
    /// Clears the screen
    write(STDOUT_FILENO, "\x1b[2J]", 4);
    /// Moves the cursor to the top left
    write(STDOUT_FILENO, "\x1b[H", 3);

    // b moves it down and c moves it over
    write(STDOUT_FILENO, "\x1b[1C\x1b[2B", 8);
    get_winsize();
    read_text_input();
    return 0;
}
