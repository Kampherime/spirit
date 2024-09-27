#include <stdio.h>
#include "./filehandling.c"

void print_intended_usage() {
    printf("Intended usage of spirit: spirit + flags + <..files>\n");
}

///Serves as an entry point for the editor. Naturally, not all operations
///will be executed in this file.
int main(int argc, char **argv) {
    if (argc == 1) {
        print_intended_usage();
    }
    read_text_input("test.txt");
    printf("%s", "Hello!!! \n");
    return 0;
}
