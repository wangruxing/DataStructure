#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */

#define COMPARE(x, y) ((x < y) ? -1: (x == y)? 0: 1)
// Program 1.4: Searching an ordered list by binary search
int binsearch(int[], int, int, int);
int main(void) {
    // list 數量
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    // 產生排序過的list
    int list[n];
    printf("your list: ");
    for(int i = 0;i < n;i++){
        list[i] = (i+1)*2;
        printf("%d ", list[i]);
    }
    printf("\n");
    // 使用者輸入欲尋找之目標數字
    int num;
    printf("Enter your target element: ");
    scanf("%d", &num);
    // 設定list的左右初始值
    int left = 0;
    int right = n-1;
    // 輸出搜尋位置結果
    printf("target element's position in the list is %d", binsearch(list, num, left, right));
}

int binsearch(int list[], int searchnum, int left, int right){
    int middle;
    while(left <= right){
        middle = (left + right) / 2;
        switch(COMPARE(list[middle], searchnum)){
            case -1: 
                left = middle + 1;
                break;
            case 0:
                return middle;
            case 1:
                right = middle - 1;
        }
    }
    return -1;
}