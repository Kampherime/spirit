#ifndef TERMINAL_HEADER
#define TERMINAL_HEADER

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <sys/ioctl.h>
#include <unistd.h>

void reset_terminal_attributes();
int set_terminal_attributes();
void enable_echoing();
void disable_echoing();
void get_winsize();

#endif
