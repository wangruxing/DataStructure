#include <stdio.h>
#include <stdlib.h>

// Program 1.1: Allocation and deallocation of memory
int main(void) {
    int i, *pi;
    float f, *pf;

    // malloc() 運算子會配置一個 int 需要的空間，並傳回該空間的位址
    pi = (int *) malloc(sizeof(int));
    pf = (float *) malloc(sizeof(float));
    printf("Original state\n");
    printf("pi : address = %p, value = %d\n", pi, *pi);
    printf("pf : address = %p, value = %f\n", pf, *pf);

    // 宣告儲存值
    *pi = 1024;
    *pf = 3.14;
    printf("Change value\n");
    printf("pi : address = %p, value = %d\n", pi, *pi);
    printf("pf : address = %p, value = %f\n", pf, *pf);
    
    // free() 釋放之前使用 malloc 或 calloc 函數所配置的記憶體空間
    free(pi);
    free(pf);
    printf("Release memory\n");
    printf("pi : address = %p, value = %d\n", pi, *pi);
    printf("pf : address = %p, value = %f\n", pf, *pf);
    return 0;
}
