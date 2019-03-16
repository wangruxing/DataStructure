#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */

// Program 1.3: Comparison of two integers
int compare(int, int);
int main(void) {
    // 亂數種子
    srand( time(NULL) );
    // 指定亂數範圍
    int min = 1;
    int max = 50;

    int x = rand() % (max - min + 1) + min;
    int y = rand() % (max - min + 1) + min;
    printf("x = %d, y = %d\nresult = %d\nx < y : -1\nx = y : 0\nx > y : 1\n", x, y, compare(x, y));
}
int compare(int x, int y){
    if (x < y)
        return -1;
    else if(x == y)
        return 0;
    else
        return 1;
}