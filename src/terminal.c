#include "terminal.h"

/// Terminal that serves as a default to go back to so this program doesn't
/// mess with the users terminal after it closes.

/* 
 * 
"\x1b[2J" - clears the screen
"\x1b[H" - puts the cursor in the top left
"\x1b[999C\x1b[999B" - moves the cursor over by a fuck ton
"\x1b[6n" - idk? useful? maybe?
"\x1b[?25l" - hide cursor
"\x1b[?25h - unhides cursor
"\x1b[%d;%dH" - mystery
*/

struct Editor_Config {
    struct termios config;
    int cx;
    int cy;
    struct winsize ws;
};

struct Editor_Config E;
struct termios default_term;

// NEVER CALL THIS WITHOUT CALLING reset_terminal_attributes() AFTER.
// ^ i fixed this
// should use atexit() for the bottom guy
int set_terminal_attributes() {
    tcgetattr(STDIN_FILENO, &E.config);
    default_term = E.config;
    struct termios raw_terminal = E.config;
    atexit(reset_terminal_attributes);

    raw_terminal.c_lflag &= ~(ICANON | IEXTEN | ISIG | ECHO);
    raw_terminal.c_cflag |= CS8;
    raw_terminal.c_iflag &= ~(BRKINT| IXON | ICRNL);
    raw_terminal.c_oflag &= ~(OPOST);
    raw_terminal.c_cc[VMIN] = 0;
    raw_terminal.c_cc[VTIME] = 1;

    tcsetattr(fileno(stdin), 0, &raw_terminal);
    E.config = raw_terminal;

    return 0;
}

/// Simply sets the terminal state back to the original state before the
/// program was opened.
void reset_terminal_attributes() {
    tcsetattr(0, TCSAFLUSH, &default_term);
}

/// Reenables ecohing
void enable_echoing() {
    E.config.c_lflag |= (ECHO);
    tcsetattr(fileno(stdin), 0, &E.config);
}

/// Disables echoing
void disable_echoing() {
    E.config.c_lflag &= ~(ECHO);
    tcsetattr(fileno(stdin), 0, &E.config);
}
/// Gets window size :) and sets the config to have it
void get_winsize() {
    struct winsize ws;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
    E.ws = ws;
}
