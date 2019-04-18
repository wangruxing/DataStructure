#include <stdio.h>
#include <stdlib.h> /* Random correlation function */
#include <time.h>   /* Time correlation function */

// 1-dimension array addressing
void print1(int*, int);
int main(void) {
    int one[] = {2, 4, 6, 8, 10};
    print1(&one[0], 5);
    return 0;
}
void print1(int *ptr, int rows){
    int i;
    printf("one   Address      Contents\n");
    for(i = 0;i < rows;i++){
        // %08u = 八位數的無符號十進位整數，不足以0填滿
        // %5d = 五位數的整數，不足以空白填滿
        printf("[%d]   %08u %5d\n", i, ptr+i, *(ptr+i));
        system("pause");
    }
}