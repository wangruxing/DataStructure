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
void fast_transpose(term a[], term b[]);
// Transpose matrix and fast transpose matrix
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
    printf("transpose\n");
    printf("before transpose  =>   after transpose\n");
    printf("row  col  value   =>   row  col  value\n");
    for(int i = 0;i < 9;i++){
        printf("%3d  %3d  %5d        ", a[i].row, a[i].col, a[i].value);
        printf("%3d  %3d  %5d\n", b[i].row, b[i].col, b[i].value);
    }
    
    fast_transpose(a, b);
    printf("\nfast_transpose\n");
    printf("before transpose  =>   after transpose\n");
    printf("row  col  value   =>   row  col  value\n");
    for(int i = 0;i < 9;i++){
        printf("%3d  %3d  %5d        ", a[i].row, a[i].col, a[i].value);
        printf("%3d  %3d  %5d\n", b[i].row, b[i].col, b[i].value);
    }
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
                if (a[j].col == i) {
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].value = a[j].value;
                    currentb++;
                }
            }
        }
    }
}

void fast_transpose(term a[], term b[]){
    int row_terms[MAX_COL], starting_pos[MAX_COL];
    int i, j;
    int num_cols = a[0].col;
    int num_terms = a[0].value;
    b[0].row = num_cols; 
    b[0].col = a[0].row;
    b[0].value = num_terms;
    if (num_terms > 0){ 
        for (i = 0; i < num_cols; i++){
            row_terms[i] = 0;
        }
        for (i = 1; i <= num_terms; i++){
            row_terms[a[i].col]++;
        }
        starting_pos[0] = 1;
        for (i = 1; i < num_cols; i++){
            starting_pos[i]=starting_pos[i-1] +row_terms [i-1];
        }
        for (i = 1; i <= num_terms; i++){
            j = starting_pos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;   
        }
    }
}