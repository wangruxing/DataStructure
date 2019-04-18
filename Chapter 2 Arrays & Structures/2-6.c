#include <stdio.h>
#include <stdlib.h> /* Random correlation function */
#include <time.h>   /* Time correlation function */
#include <string.h>
#define MAX_COL 101 
#define MAX_TERMS 101 /* maximum number of terms +1*/
#define COMPARE(x,y) ((x < y) ? -1: (x == y)? 0: 1)

typedef struct {
    int row;
    int col;    
    int value;
} term;
term a[MAX_TERMS];
term b[MAX_TERMS];
term d[MAX_TERMS];
term newB[MAX_TERMS];

void fast_transpose(term a[], term b[]);
void mmult (term a[], term b[], term d[]);
void storeSum(term d[], int *totalD, int row, int column, int *sum);

// Sparse Matrix Multiplication
int main(void) {
    a[0].row = 3;
    a[0].col = 3;
    a[0].value = 3;
    a[1].row = 0;
    a[1].col = 0;
    a[1].value = 1;
    a[2].row = 1;
    a[2].col = 0;
    a[2].value = 2;
    a[3].row = 2;
    a[3].col = 0;
    a[3].value = 3;

    b[0].row = 3;
    b[0].col = 3;
    b[0].value = 3;
    b[1].row = 0;
    b[1].col = 0;
    b[1].value = 1;
    b[2].row = 0;
    b[2].col = 1;
    b[2].value = 2;
    b[3].row = 0;
    b[3].col = 2;
    b[3].value = 3;
    mmult (a, b, d);
    printf("       a                      b                    newB                     d\n");
    printf("row  col  value        row  col  value        row  col  value        row  col  value\n");
    for(int i = 0;i < 10;i++){
        printf("%3d  %3d  %5d        ", a[i].row, a[i].col, a[i].value);
        printf("%3d  %3d  %5d        ", b[i].row, b[i].col, b[i].value);
        printf("%3d  %3d  %5d        ", newB[i].row, newB[i].col, newB[i].value);
        printf("%3d  %3d  %5d\n", d[i].row, d[i].col, d[i].value);
    }
    return 0;
}
/* if *sum != 0, then it along with its row and column
    position is stored as the *totald+1 entry in d */
void storeSum(term d[], int *totalD, int row, int column, int *sum){  
    if (*sum){
        if (*totalD < MAX_TERMS) {
            d[++*totalD].row = row;
            d[*totalD].col = column;
            d[*totalD].value = *sum;
        } else {
            fprintf(stderr, "Numbers of terms in product exceed %d\n", MAX_TERMS);
            exit(1);
        }
    }
}

void fast_transpose(term a[], term b[]){
    /* the transpose of a is placed in b */
    int row_terms[MAX_COL], starting_pos[MAX_COL];
    int i, j;
    int num_cols = a[0].col;
    int num_terms = a[0].value;
    b[0].row = num_cols; 
    b[0].col = a[0].row;
    b[0].value = num_terms;
    if (num_terms > 0){ /* nonzero matrix */
        for (i = 0; i < num_cols; i++){
            row_terms[i] = 0;
        }
        for (i = 1; i <= num_terms; i++){ /* Calculation row_terms */
            row_terms[a[i].col]++;
        }
        starting_pos[0] = 1;
        for (i = 1; i < num_cols; i++){
            starting_pos[i]=starting_pos[i-1] +row_terms [i-1];/* Calculation starting_pos */
        }
        for (i = 1; i <= num_terms; i++){
            j = starting_pos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;   
        }
    }
}

void mmult (term a[], term b[], term d[]){
    int i, j, column, totalD = 0;
    int rowsA = a[0].row;
    int colsA = a[0].col;
    int totalA = a[0].value; 
    int colsB = b[0].col;
    int totalB = b[0].value;
    int rowBegin = 1, row = a[1].row, sum;
    if (colsA != b[0].row){
        fprintf (stderr, "Incompatible matrices\n");
        exit (1);
    }
    fast_transpose(b, newB); 
    /* set boundary condition */
    a[totalA+1].row = rowsA;    // a[4].row=3
    newB[totalB+1].row = colsB; // newB[4].row=3
    newB[totalB+1].col = 0;     // newB[4].col=0

    for (i = 1; i <= totalA; ) {
        printf("Round %d: \n", i); 
        column = newB[1].row;
        sum = 0;
        for (j = 1; j <= totalB+1;) {    
            printf("i=%d, j=%d, a[%d].row=%d, row=%d\n", i, j, i, a[i].row, row);    
            if (a[i].row != row) {
                printf("a[%d].row=%d != row=%d\n", i, a[i].row, row);   
                storeSum(d, &totalD, row, column, &sum);
                printf("      d\n");
                printf("row  col  value\n");
                for(int i = 0;i <= totalD;i++){
                    printf("%3d  %3d  %5d\n", d[i].row, d[i].col, d[i].value);
                }
                i = rowBegin;
                printf("i=%d\t", i);
                for (; newB[j].row == column; j++) ;
                printf("j=%d\t", j);
                column =newB[j].row;
                printf("column=%d\n", column);
            }else if(newB[j].row != column){      
                printf("newB[%d].row=%d != column=%d\n", j, newB[j].row, column); 
                storeSum(d, &totalD, row, column, &sum);
                printf("      d\n");
                printf("row  col  value\n");
                for(int i = 0;i <= totalD;i++){
                    printf("%3d  %3d  %5d\n", d[i].row, d[i].col, d[i].value);
                }
                i = rowBegin;
                printf("i=%d\t", i);
                column = newB[j].row;
                printf("column=%d\n", column);
            }else switch (COMPARE (a[i].col, newB[j].col)) {               
                case -1:   
                    printf("COMPARE: a[%d].col=%d < newB[%d].col=%d => case -1\n", i, a[i].col, j, newB[j].col);    
                    i++;   
                    printf("i=%d\n", i);
                    break;
                case 0:  
                    printf("COMPARE: a[%d].col=%d = newB[%d].col=%d => case 0\n", i, a[i].col, j, newB[j].col);  
                    sum = (a[i++].value * newB[j++].value);
                    printf("a[i++].value=%d\n", a[i-1].value);
                    printf("newB[j++].value=%d\n", newB[j-1].value);
                    printf("sum=%d\ti=%d\tj=%d\t\n",sum, i, j);
                    break;
                case 1:    
                    printf("COMPARE: a[%d].col=%d > newB[%d].col=%d => case 1\n", i, a[i].col, j, newB[j].col);
                    j++;
                    printf("j=%d\n", j);
            }
            printf("-------------------------------------------------\n");
            
        }
        for (; a[i].row == row; i++) ;
        printf("i=%d\t", i);
        rowBegin = i; row = a[i].row;
        printf("rowBegin=%d\t", rowBegin);
        printf("row=%d\n", row);
        printf("*************************************************\n");
    } 
    d[0].row = rowsA; 
    d[0].col = colsB; 
    d[0].value = totalD;
} 

