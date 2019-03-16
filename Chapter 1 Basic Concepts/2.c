#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */

// Program 1.15: Program 1.12 with count statements added   27
int rsum(int[], int, int);
int main(void) {
    int n = 5;
    printf("n=%d\n", n);
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
    rsum(list, n, count);

    return 0;
}

int rsum(int list[], int n, int count){
    
    count++;
    printf("\"if(n)\", count=%d\n", count);
    if(n){
        count++;
        printf("\"return rsum(list, n-1) + list[n-1];\", count=%d\n", count);
        return rsum(list, n-1, count) + list[n-1];
    }
    count++;
    printf("\"return list[0];\", count=%d\n", count);
    return list[0];
}