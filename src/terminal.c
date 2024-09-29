#include <termios.h>
#include <stdio.h>

struct termios original_terminal;

void set_terminal_attributes() {
    struct termios raw_terminal;
    tcgetattr(0, &original_terminal);
    tcgetattr(fileno(stdin), &raw_terminal);
    cfmakeraw(&raw_terminal);
    tcsetattr(fileno(stdin), 0, &raw_terminal);

}

void reset_terminal_attributes() {
    tcsetattr(0, TCSAFLUSH, &original_terminal);
}
