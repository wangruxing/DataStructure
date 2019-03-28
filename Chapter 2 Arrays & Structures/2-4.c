#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */
#include <string.h>

#define MAX_TERMS 101 /* maximum number of terms +1*/
#define MAX_COL 101 

typedef struct {
    int row;
    int col;    
    int value;
} term;
term a[MAX_TERMS];
term b[MAX_TERMS];

void transpose (term a[], term b[]);
// Transpose matrix
int main(void) {
    a[0].row = 6;
    a[0].col = 6;
    a[0].value = 8;
    a[1].row = 0;
    a[1].col = 0;
    a[1].value = 15;
    a[2].row = 0;
    a[2].col = 3;
    a[2].value = 22;
    a[3].row = 0;
    a[3].col = 5;
    a[3].value = -15;
    a[4].row = 1;
    a[4].col = 1;
    a[4].value = 11;
    a[5].row = 1;
    a[5].col = 2;
    a[5].value = 3;
    a[6].row = 2;
    a[6].col = 3;
    a[6].value = -6;
    a[7].row = 4;
    a[7].col = 0;
    a[7].value = 91;
    a[8].row = 5;
    a[8].col = 2;
    a[8].value = 28;
    
    transpose (a, b);
    printf("Transposed matrix result\n");
    printf("before transpose  =>   after transpose\n");
    printf("row  col  value   =>   row  col  value\n");
    for(int i = 0;i < 9;i++){
        printf("%3d  %3d  %5d        ", a[i].row, a[i].col, a[i].value);
        printf("%3d  %3d  %5d\n", b[i].row, b[i].col, b[i].value);
    }
    printf("\n\n");
    return 0;
}

void transpose (term a[], term b[]){
    int n, i, j, currentb;
    n = a[0].value; 
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = n;
    if (n > 0) {
        currentb = 1;
        for (i = 0; i < a[0].col; i++){
            for(j = 1; j <= n; j++){
                printf("i=%d, j=%d, a[j].col=%d\n", i, j, a[j].col);
                if (a[j].col == i) {
                    printf("(a[%d].col=%d) == (i=%d)\n", j, a[j].col, i);
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[j].value;
                    currentb++;
                    printf("before transpose  =>   after transpose\n");
                    printf("row  col  value   =>   row  col  value\n");
                    for(int i = 0;i < 9;i++){
                        printf("%3d  %3d  %5d        ", a[i].row, a[i].col, a[i].value);
                        printf("%3d  %3d  %5d\n", b[i].row, b[i].col, b[i].value);
                    }
                    printf("-------------------------------------------------\n"); 
                }
            }
            printf("*************************************************\n");
        }
    }
}
