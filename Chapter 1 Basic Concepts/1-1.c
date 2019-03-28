#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */

// Program 1.13: Program 1.11 with count statements
int main(void) {
    int n = 5;
    printf("Loop execution times=%d\n", n);
    // 亂數種子
    srand( time(NULL) );
    // 指定亂數範圍
    int min = 1;
    int max = n+100;
    // 隨機產生n個整數
    int list[n];
    for(int i = 0;i < n;i++){
        list[i] = rand() % (max - min + 1) + min;
    }
    int count = 0;
    float tempsum = 0;
    count++;
    printf("\"float tempsum = 0;\", count=%d\n", count);
    int i;
    for(i = 0;i < n;i++){
        count++;
        printf("\"for(i = 0;i < n;i++)\",i=%d, count=%d\n", i, count);
        tempsum += list[i];
        count++;
        printf("\"tempsum += list[i];\", count=%d\n", count);
    }
    count++;
    printf("last execution of for, count=%d\n", count);
    count++;
    printf("\"return 0;\", count=%d\n", count);
    return 0;
}