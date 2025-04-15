#ifndef FILEHANDLING_HEADER
#define FILEHANDLING_HEADER

#include <stdio.h>
#include <unistd.h> //for read and stdin_fileno
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "terminal.h"
#include "data.h"
#include "controls.h"


typedef struct {
    bool isNormalMode;
    bool isInsertMode;
} Terminal_Status;

int movement_loop();
int read_text_input(Terminal_Status *TS);

#endif
