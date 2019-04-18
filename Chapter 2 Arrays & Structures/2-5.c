#include <stdio.h>
#include <stdlib.h> /* Random correlation function */
#include <time.h>   /* Time correlation function */
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

void fast_transpose(term a[], term b[]);
// Fast transpose matrix
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
    
    fast_transpose(a, b);
    printf("Fast transpose matrix result\n");
    printf("before transpose  =>   after transpose\n");
    printf("row  col  value   =>   row  col  value\n");
    for(int i = 0;i < 9;i++){
        printf("%3d  %3d  %5d        ", a[i].row, a[i].col, a[i].value);
        printf("%3d  %3d  %5d\n", b[i].row, b[i].col, b[i].value);
    }
    return 0;
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
        printf("Initial row_terms\ni     ");
        for (i = 0; i < num_cols; i++){
            printf("%2d ", i);
        }
        printf("\nvalue ");
        for (i = 0; i < num_cols; i++){
            row_terms[i] = 0;
            printf("%2d ",row_terms[i]);
        }
        printf("\n\n");
        
        printf("Calculation row_terms\n");
        for (i = 1; i <= num_terms; i++){
            row_terms[a[i].col]++;
            printf("a[%d].col=%d\n", i, a[i].col);
            printf("row_terms\ni     ");
            for (j = 0; j < num_cols; j++){
                printf("%2d ", j);
            }
            printf("\nvalue ");
            for (j = 0; j < num_cols; j++){
                printf("%2d ",row_terms[j]);
            }
            printf("\n");
            printf("-----------------------\n");
        }
        printf("\n");

        starting_pos[0] = 1;
        printf("Calculation starting_pos\n");
        for (i = 1; i < num_cols; i++){
            starting_pos[i] = starting_pos[i-1] + row_terms [i-1];
            printf("starting_pos[i=%d] = (starting_pos[i-1=%d]=%d) + (row_terms [i-1=%d]=%d)\n", i, i-1,starting_pos[i-1], i-1, row_terms [i-1]);
            printf("starting_pos\ni     ");
            for (j = 0; j <= i; j++){
                printf("%2d ", j);
            }
            printf("\nvalue ");
            for (j = 0; j <= i; j++){
                printf("%2d ",starting_pos[j]);
            }
            printf("\n");
            printf("-----------------------\n");
        }
        printf("\n");

        printf("Transposition process\n");
        for (i = 1; i <= num_terms; i++){
            j = starting_pos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;  
            printf("Transposed position=%d\n", j);   
            printf("i  row  col  value\n");
            for(int z = 0;z < 9;z++){
                printf("%d  %3d  %3d  %5d\n", z, b[z].row, b[z].col, b[z].value);
            }
            printf("-----------------------\n");
        }
    }
}