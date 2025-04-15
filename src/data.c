#include "data.h"

#define DEFAULT_CAPACITY 10 //jic

// The struct that will hold the 2D array. Needs to be dynamically allocated.
/// Holds the values for the columns and rows of the cursor.
/// Inits and returns a struct. Acts like a constructor for a class, almost.
CharVector init_char_vector() {
    char* array_block = (char*) calloc(DEFAULT_CAPACITY, sizeof(char)); // yes i know sizeof(char) is 1 but java taught me to hate magic numbers
    CharVector vec = {array_block, 0, DEFAULT_CAPACITY};
    return vec;
}

// Returns an error code, hence the int return
/// Whenever the CharVector is maxxed out, this function should be called 
/// to double its size.
int resize_char_vector(CharVector *vec) {
    const int ARRAY_SIZE = vec->capacity*2;
    char* new_array = realloc(vec->char_array, ARRAY_SIZE);
    if (new_array == NULL) {
        return 1;
    }
    vec->capacity *= 2;
    //free(vec->char_array); // Might literally crash the program (it does.)
    vec->char_array = new_array;
    return 0;
}
