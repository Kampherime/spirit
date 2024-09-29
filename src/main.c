#include <stdio.h>
#include "./filehandling.c"
#include "./terminal.c"

void print_intended_usage() {
    printf("Intended usage of spirit: spirit + flags + <..files>\n");
}

///Serves as an entry point for the editor. Naturally, not all operations
///will be executed in this file.
int main(int argc, char **argv) {
    struct termios original_term;
    if (argc == 1) {
        // This is commented out because every time we run make run, it runs.
        //print_intended_usage();
    }
    set_terminal_attributes();
    read_text_input();
    reset_terminal_attributes(original_term);
    return 0;
}
