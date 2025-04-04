#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"

/// Terminal that serves as a default to go back to so this program doesn't
/// mess with the users terminal after it closes.

struct Editor_Config {
    struct termios config;
};

struct Editor_Config E;

/// uses cfmakeraw() to allow for raw input to the terminal.
/// NEVER CALL THIS WITHOUT CALLING reset_terminal_attributes() AFTER.
/// ^ i fixed this
/// should use atexit() for the bottom guy
int set_terminal_attributes() {
    tcgetattr(fileno(stdin), &E.config);
    struct termios raw_terminal = E.config;
    atexit(reset_terminal_attributes);

    raw_terminal.c_lflag &= ~(ICANON | IEXTEN | ISIG);
    raw_terminal.c_cflag |= CS8;
    raw_terminal.c_iflag &= ~(BRKINT| IXON | ICRNL);
    raw_terminal.c_oflag &= ~(OPOST);
    raw_terminal.c_cc[VMIN] = 0;
    raw_terminal.c_cc[VTIME] = 1;

    tcsetattr(fileno(stdin), 0, &raw_terminal);

    return 0;
}

/// Simply sets the terminal state back to the original state before the
/// program was opened.
void reset_terminal_attributes() {
    tcsetattr(0, TCSAFLUSH, &E.config);
}
