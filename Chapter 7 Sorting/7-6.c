// C++ program for implementation of Heap Sort 
#include <stdio.h>
#include <stdlib.h>

void heapify(int arr[], int n, int i) ;
void heapSort(int arr[], int n);
void printArray(int arr[], int n);

int arr[] = {26, 5, 77, 1, 61, 11, 59, 15, 48, 19}; 
int n = sizeof(arr)/sizeof(arr[0]);
int len = sizeof(arr)/sizeof(arr[0]); 

// To heapify a subtree rooted with node i which is 
// an index in arr[]. n is size of heap 
void heapify(int arr[], int n, int i) { 
	int largest = i; // Initialize largest as root 
	int l = 2*i + 1; // left = 2*i + 1 
	int r = 2*i + 2; // right = 2*i + 2 

	// If left child is larger than root 
	if (l < n && arr[l] > arr[largest]) 
		largest = l; 

	// If right child is larger than largest so far 
	if (r < n && arr[r] > arr[largest]) 
		largest = r; 

	// If largest is not root 
	if (largest != i){ 
        // swap
        printf("Root arr[%d] is not largest number: swap(%d, %d)\n", i, arr[i], arr[largest]);
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        printArray(arr, len);
        for(int k = 0;k < len;k++){
            if(k == largest || k == i)
                printf("-- ");
            else
                printf("   "); 
        }
        puts("\n");
		// Recursively heapify the affected sub-tree 
		heapify(arr, n, largest); 
	} 
} 

// main function to do heap sort 
void heapSort(int arr[], int n) { 
	// Build heap (rearrange array) 
	for (int i = n / 2 - 1; i >= 0; i--){
		heapify(arr, n, i); 
    }
	// One by one extract an element from heap 
	for (int i=n-1; i>=0; i--) { 
		// swap: Move current root to end  
        printf("Move current root arr[0] to end: swap(%d, %d)\n", arr[0], arr[i]);
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
		// Output step by step
        printArray(arr, n);
        for(int k = 0;k < len;k++){
            if(k == 0 || k == i)
                printf("-- ");
            else
                printf("   "); 
        }
        puts("\n");
		// call max heapify on the reduced heap 
		heapify(arr, i, 0); 

	} 
} 

/* A utility function to print array of size n */
void printArray(int arr[], int n) { 
	for (int i=0; i<n; ++i) 
		printf("%2d ", arr[i]); 
	printf("\n"); 
} 

// Driver program 
int main(){ 
	
    printArray(arr, len);
	heapSort(arr, n); 

	puts("Result: Sorted array is "); 
	printArray(arr, n); 
} 
