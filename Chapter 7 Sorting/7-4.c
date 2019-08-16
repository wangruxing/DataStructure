#define SIZE 10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
// Quick sort
// structure                            
typedef struct {                                           
   int key; // node value                               
}element ;
element a[SIZE];

void quicksort(element a[], int left, int right);

int main(void){
    int i, data[SIZE];
    int value;

    // 26 5 37 1 61 11 59 15 48 19
    // input data
    printf("%s", "Please enter ten integers: ");
    for ( i = 0; i < SIZE; i++ ){
	    scanf("%2d", &a[i].key);
    }

    // show data before sorting
    printf("Unsorted array: \n");
    printf("                        ");
    for ( i = 0; i < SIZE; i++ ){ 
        printf( "%2d  ", a[i].key ); /* print the array */
    }
    printf("\n");

    // execute quick sort
    quicksort(a, 0, SIZE - 1);

    // show data after sorting
    printf("Sorted array: ");
    for (i = 0; i < SIZE; i++){
        printf("%2d  ", a[i].key);
    }
    printf("\n");
}

void quicksort(element a[], int left, int right){
    int pivot, i, j;
    element temp;
    if(left < right){
        i = left;
        j = right + 1;
        pivot = a[left].key;
        // until the left and right boundaries cross or meet
        do{
            // search value from left side until a[i].key > pivot 
            do 
                i++; 
            while(a[i].key < pivot);
            // search value from right side until a[j].key < pivot 
            do 
                j--; 
            while(a[j].key > pivot);
            // swap
            if (i < j){
                SWAP(a[i], a[j], temp);   
                // Output step by step
                printf("    i, j: %2d swap %2d -> ",a[i].key, a[j].key);
                for (int z = 0; z < SIZE; z++){
                    printf("%2d  ", a[z].key);
                }
                printf("\n                        ");
                for (int k = 0; k < SIZE; ++k)
                    if(k == i || k == j)
                        printf( "%s", "--  " );
                    else
                        printf( "%s", "    " );  
                printf("\n");          
            }
        } while(i < j);
        SWAP(a[left], a[j], temp);
        // Output step by step
        printf("pivot, j: %2d swap %2d -> ",a[left].key, a[j].key);
        for (i = 0; i < SIZE; i++){
            printf("%2d  ", a[i].key);
        }
        printf("\n                        ");
        for (int k = 0; k < SIZE; ++k)
            if(k == left || k == j)
                printf( "%s", "--  " );
            else
                printf( "%s", "    " );  
        printf("\n");
        quicksort(a, left, j-1);  // execute quick sort on the left side
        quicksort(a, j+1, right); // execute quick sort on the right side
    }
}

/*

 */

/*

 */