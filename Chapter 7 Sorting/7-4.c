#define SIZE 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quicksort(int *data, int left, int right);
void swap(int *a, int *b);

int main(void){
    int i, data[SIZE];
    srand( time( NULL ) ); /* seed the rand function */
    for ( i = 0; i < SIZE; i++ )
        data[ i ] = rand() % 90 + 10; /* give each element a value */  
    printf("Unsorted array: \n");
    printf("              ");
    for ( i = 0; i < SIZE; i++ ) /* print the array */
        printf( "%d  ", data[ i ] );
    printf("\n");
    // execute quick sort
    quicksort(data, 0, SIZE - 1);

    printf("Sorted array: ");
    for (i = 0; i < SIZE; i++){
        printf("%d  ", data[i]);
    }
    printf("\n");
}

void quicksort(int *data, int left, int right)
{
    int pivot, i, j;
    if (left >= right) { return; }
    pivot = data[left];
    i = left + 1;
    j = right;
    while (1){
        while (i <= right){
            if (data[i] > pivot){ break;}
            i = i + 1;
        }
        while (j > left){
            if (data[j] < pivot){
                break;
            }
            j = j - 1;
        }
        if (i > j) { break; }
        swap(&data[i], &data[j]);
        // Output step by step
        printf("%d swap %d -> ",data[i], data[j]);
        for (int z = 0; z < SIZE; z++){
            printf("%d  ", data[z]);
        }
        printf("\n              ");
        for (int k = 0; k < SIZE; ++k)
            if(k == i || k == j)
                printf( "%s", "--  " );
            else
                printf( "%s", "    " );  
        printf("\n");  
    }

    swap(&data[left], &data[j]);
    // Output step by step
    printf("%d swap %d -> ",data[left], data[j]);
    for (i = 0; i < SIZE; i++){
        printf("%d  ", data[i]);
    }
    printf("\n              ");
    for (int k = 0; k < SIZE; ++k)
        if(k == left || k == j)
		    printf( "%s", "--  " );
        else
            printf( "%s", "    " );  
    printf("\n");  
    
    quicksort(data, left, j - 1);
    quicksort(data, j + 1, right);
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}