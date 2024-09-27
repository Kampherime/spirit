#include <stdio.h>
#include <unistd.h> //for read and stdin_fileno
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//#define DEFAULT_CAPACITY = 10;

typedef struct {
    char *char_array;
    int size;
    int capacity;
} CharVector;

CharVector init_char_vector() {
    void* array_block = malloc(10);
    char* default_array = (char *) memset(array_block, 0, 10);
    CharVector vec = {default_array, 0, 10};
    return vec;
}

/// Returns an error code, hence the int return
int resize_char_vector(CharVector *vec) {
    const int ARRAY_SIZE = vec->capacity*2;
    char* new_array = realloc(vec->char_array, ARRAY_SIZE);
    if (new_array == NULL) {
        fprintf(stderr, "ERROR: Failed to realloc a larger array capacity.");
        return 1;
    }
    vec->capacity *= 2;
    memmove(new_array, vec->char_array, vec->size);
    //free(vec->char_array); // Might literally crash the program
    vec->char_array = new_array;
    return 0;
}


/// Returns an error code, hence the int return
int read_text_input(char* filePath) {
    CharVector input_vector = init_char_vector(); 
    char buff[10];
    FILE* file = fopen(filePath, "w"); 
    if (file == NULL) {
        fprintf(stderr, "ERROR: Error opening file.\n");
        return 1; // Can't decide if this should be return 1 or exit(1);
    }
    while(fgets(buff, 10, stdin) != NULL) {
        if (input_vector.size + 10 > input_vector.capacity) {
            int res = resize_char_vector(&input_vector);
            if (res != 0) {
                break;
            }
        }
        strcat(input_vector.char_array, buff);
        printf("This is the string. No error yet: %s\n", input_vector.char_array);
    }
    fclose(file);
    free(input_vector.char_array);
    input_vector.char_array = NULL;
    return 0;
}
