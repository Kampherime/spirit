#ifndef DATA_HEADER
#define DATA_HEADER

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char*** array;
} FileData;

/// The struct for a resizable string. Similar to an ArrayList from Java.
typedef struct {
    char *char_array;
    int size;
    int capacity;
} CharVector;

/// Holds the values for the columns and rows of the cursor.

/// Inits and returns a struct. Acts like a constructor for a class, almost.
CharVector init_char_vector();

// Returns an error code, hence the int return
/// Whenever the CharVector is maxxed out, this function should be called 
/// to double its size.
int resize_char_vector(CharVector *vec);

#endif
