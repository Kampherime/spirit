#include <termios.h>
#include <stdio.h>

void set_terminal_attributes() {
    struct termios raw_terminal;
    tcgetattr(fileno(stdin), &raw_terminal);
    cfmakeraw(&raw_terminal);
    tcsetattr(fileno(stdin), 0, &raw_terminal);

}

void reset_terminal_attributes(struct termios original) {
    tcsetattr(fileno(stdin), 0, &original);
}
