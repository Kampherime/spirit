#ifndef CONTROL_HEADER
#define CONTROL_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>


/// Will hold all the special escape codes for the program to read.
enum EscapeCodes {
    CTRL_Q = 17,
    LEFT = 104,
    DOWN = 106,
    UP = 107,
    RIGHT = 108,
    ESC = 27
};

int process_escape_codes(char c, bool isNormalMode);
int move_cursor(int input);

#endif
