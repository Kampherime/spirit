#include <stdio.h>



int main(void) {
    printf("%s\n%s\n%s\n%s\n%s\n", "This is the test suite.", 
           "As tests get written, add them here and run 'make tests'",
           "It is good practice to make each test its own method",
           "Run 'make -s tests' to disable the echoing of commands",
           "This makes the test suite cleaner and easier to read.");
    return 0;
}
