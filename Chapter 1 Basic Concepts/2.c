#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */

// Program 1.2: Selection sort algorithm
int SeleSort(int, int[]);
int main(void) {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    // 亂數種子
    srand( time(NULL) );
    // 指定亂數範圍
    int min = 1;
    int max = n+100;
    // 隨機產生n個整數
    int arr[n];
    for(int i = 0;i < n;i++){
        arr[i] = rand() % (max - min + 1) + min;
    }
    // 顯示排序前的list
    printf("Your initial list:");
    for(int i = 0;i < n;i++){
       printf(" %d", arr[i]);
    }
    printf("\n");
    // 選擇排序法
    SeleSort(n, arr);
    return 0;
}
int SeleSort(int n, int arr[]){
    for (int c = 0; c < n-1; c++){
        int position = c;
        int swap;
        for (int d = c + 1; d < n; d++){
            if (arr[position] > arr[d])
                position = d;
        }
        printf("\nstep %d:", c+1);
        for(int i = 0;i < n;i++){
            printf(" %d", arr[i]);
        }
        printf("\nposition= %d, position value= %d, min = %d",c, arr[c], arr[position]);
        if (position != c){    
            swap = arr[c]; 
            arr[c] = arr[position];
            arr[position] = swap;
            printf(" => (position value != min) => swap\n");
        }
        else
            printf("\n");
    }
    printf("\nyour list after sorting:");
    for(int i = 0;i < n;i++){
        printf(" %d", arr[i]);
    }
}