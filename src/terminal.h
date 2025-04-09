#pragma once

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include <sys/ioctl.h>

void reset_terminal_attributes();
int set_terminal_attributes();
