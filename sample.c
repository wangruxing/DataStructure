#include <stdio.h>
#include <stdlib.h> /* Random correlation function */
#include <time.h>   /* Time correlation function */
#include <string.h>
#define COMPARE(x, y) ((x < y) ? -1: (x == y)? 0: 1)
#define MALLOC(p, s) \
    if(!((p) = malloc(s))){ \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
// example
int main(void) {
    return 0;
}