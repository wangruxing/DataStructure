#define SIZE 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* The Bubble Sort algorithm. */
void BubbleSort(int arr[], int len){
	int i, j, temp;
	for (i = 0; i < len - 1; ++i){          //循環N-1次
        printf("i = %d\n", i);
		for (j = 0; j < len - 1 - i; ++j){  //每次循環要比較的次數
			if (arr[j] > arr[j + 1]){       //比大小後交換
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
                printf("%d swap %d -> ", arr[j], arr[j + 1]);
                for (int k = 0; k < SIZE; ++k)
		            printf("%d  ", arr[k]);
                printf("\n");
                printf("              ");
                for (int k = 0; k < SIZE; ++k)
                    if(k == j || k == j+1)
		                printf( "%s", "--  " );
                    else
                        printf( "%s", "    " );
                printf("\n");
			}
        }
    } 
}

int main() 
{
    int i;
	int arr[SIZE];

    srand( time( NULL ) ); /* seed the rand function */
    for ( i = 0; i < SIZE; i++ )
        arr[ i ] = rand() % 90 + 10; /* give each element a value */  
    printf("Unsorted array:\n");
    printf("              ");
    for ( i = 0; i < SIZE; i++ ) /* print the array */
        printf( "%d  ", arr[ i ] );
    printf("\n");    
	BubbleSort(arr, SIZE);	
	return 0;
}