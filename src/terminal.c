#include <termios.h>
#include <stdio.h>

/// Terminal that serves as a default to go back to so this program doesn't
/// mess with the users terminal after it closes.
struct termios original_terminal;

/// uses cfmakeraw() to allow for raw input to the terminal.
/// NEVER CALL THIS WITHOUT CALLING reset_terminal_attributes() AFTER.
void set_terminal_attributes() {
    struct termios raw_terminal;
    tcgetattr(0, &original_terminal);
    tcgetattr(fileno(stdin), &raw_terminal);
    cfmakeraw(&raw_terminal);
    tcsetattr(fileno(stdin), 0, &raw_terminal);

}

/// Simply sets the terminal state back to the original state before the
/// program was opened.
void reset_terminal_attributes() {
    tcsetattr(0, TCSAFLUSH, &original_terminal);
}
