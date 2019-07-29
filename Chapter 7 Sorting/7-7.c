#include <stdio.h> 
#include <stdlib.h> 

void radixSort(int[]);

int main(void) { 
    // 73, 22, 93, 43, 55, 14, 28, 65, 39, 81
    int data[] = {179, 208, 306, 93, 859, 984, 55, 9, 271, 33}; 
      
    printf("Before sorting: \n"); 
    int i;
    for(i = 0; i < 10; i++) 
        printf("%3d ", data[i]); 

    printf("\n\n");

    radixSort(data);
    
    printf("After sorting: \n"); 
    for(i = 0; i < 10; i++) 
        printf("%3d ", data[i]); 

    return 0; 
} 

void radixSort(int data[]) {
    int temp[10][10] = {0}; 
    int order[10] = {0}; 
    int time = 0;
    int n = 1; 
    while(n <= 100) { 
        time++;
        int i;
        for(i = 0; i < 10; i++) { 
            int lsd = ((data[i] / n) % 10); 
            temp[lsd][order[lsd]] = data[i]; 
            order[lsd]++; 
        } 
        
        // Reorganize
        int k = 0;
        for(i = 0; i < 10; i++) { 
            if(order[i] != 0)  {
                int j;
                for(j = 0; j < order[i]; j++, k++) { 
                    data[k] = temp[i][j]; 
                } 
            }
            order[i] = 0; 
        } 
        printf("%d-pass queues and result\n", time);
        for(int p = 0; p < 10; p++) 
            printf("%3d ", data[p]); 
        printf("\n\n");
        n *= 10; 
    }     
}