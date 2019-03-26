#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */

// 1-dimension array addressing
void print1(int*, int);
int main(void) {
    int one[] = {0, 1, 2, 3, 4};
    print1(&one[0], 5);
    return 0;
}
void print1(int *ptr, int rows){
    int i;
    printf("Address      Contents\n");
    for(i = 0;i < rows;i++){
        // %08u = 八位數的無符號十進位整數，不足以0填滿
        // %5d = 五位數的整數，不足以空白填滿
        printf("%08u %5d\n", ptr+i, *(ptr+i));
    }
}