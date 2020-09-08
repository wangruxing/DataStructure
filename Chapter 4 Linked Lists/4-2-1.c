#include <stdio.h>
#include <stdlib.h> 


int main(void) {
    int ball = 5;
    int *ptr;
    ptr = &ball;
}


    printf("ball=%d\n", ball);
    printf("&ball=%p\n", &ball);
    printf("ptr=%p\n", ptr);
    printf("*ptr=%d\n", *ptr);
    printf("&ptr=%p\n", &ptr);
    printf("*&ptr=%p\n", *&ptr);
    printf("&*ptr=%p\n", &*ptr);
