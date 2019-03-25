#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */
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
    a[1].value = 2;
    a[2].row = 1;
    a[2].col = 0;
    a[2].value = 1;
    a[3].row = 2;
    a[3].col = 0;
    a[3].value = 1;

    b[0].row = 3;
    b[0].col = 3;
    b[0].value = 3;
    b[1].row = 0;
    b[1].col = 0;
    b[1].value = 3;
    b[2].row = 0;
    b[2].col = 1;
    b[2].value = 1;
    b[3].row = 0;
    b[3].col = 2;
    b[3].value = 1;
    mmult (a, b, d);
    printf("       a          =>          b          =>          d\n");
    printf("row  col  value   =>   row  col  value   =>   row  col  value\n");
    for(int i = 0;i < 10;i++){
        printf("%3d  %3d  %5d        ", a[i].row, a[i].col, a[i].value);
        printf("%3d  %3d  %5d        ", b[i].row, b[i].col, b[i].value);
        printf("%3d  %3d  %5d\n", d[i].row, d[i].col, d[i].value);
    }
    return 0;
}
void storeSum(term d[], int *totalD, int row, int column, int *sum)
{
    /* if *sum != 0, then it along with its row and column
    position is stored as the *totald+1 entry in d */
    if (*sum){
        if (*totalD < MAX_TERMS) {
            d[++*totalD].row = row;
            d[*totalD].col = column;
            d[*totalD].value = *sum;
        }
        else {
            fprintf(stderr, "Numbers of terms in product exceed %d\n", MAX_TERMS);
            exit(1);
        }
    }
}

void fast_transpose(term a[], term b[])
{
    /* the transpose of a is placed in b */
    int row_terms[MAX_COL], starting_pos[MAX_COL];
    int i, j;
    int num_cols = a[0].col;
    int num_terms = a[0].value;
    b[0].row = num_cols; 
    b[0].col = a[0].row;
    b[0].value = num_terms;
    if (num_terms > 0){ /*nonzero matrix*/
        for (i = 0; i < num_cols; i++){
            row_terms[i] = 0;
        }
        for (i = 1; i <= num_terms; i++){ /*計算 row_terms的值*/
            row_terms[a[i].col]++;
        }
        starting_pos[0] = 1;
        for (i = 1; i < num_cols; i++){
            starting_pos[i]=starting_pos[i-1] +row_terms [i-1];/*計算 starting_pos的值*/
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
/* multiply two sparse matrices */
    int i, j, column, totalB = b[0].value, totalD = 0;
    int rowsA = a[0].row;
    int colsA = a[0].col;
    int totalA = a[0].value; 
    int colsB = b[0].col;
    int rowBegin = 1, row = a[1].row, sum;
    if (colsA != b[0].row){
    /*compare the row of a and the col of b*/
        fprintf (stderr, "Incompatible matrices\n");
        exit (1);
    }
    fast_transpose(b, newB); /* the transpose of b is placed in new_b */
    /* set boundary condition */
    a[totalA+1].row = rowsA; /* a[0].row*/
    newB[totalB+1].row = colsB;
    newB[totalB+1].col = 0;
    for (i = 1; i <= totalA; ) { /* totalA = a[0].val */
        column = newB[1].row; /* b[1].col*/
        sum = 0;
        for (j = 1; j <= totalB+1;) { /* totalB = b[0].val*/
        /* mutiply row of a by column of b */
            if (a[i].row != row) { /* row = a[1].row */
                storeSum(d, &totalD, row, column, &sum);
                i = rowBegin;
                for (; newB[j].row == column; j++)
                    ;
                column =newB[j].row;
            }
            else if(newB[j].row != column){ /* column = newB[1].row */
                storeSum(d, &totalD, row, column, &sum);
                i = rowBegin;
                column = newB[j].row;
            }
            else switch (COMPARE (a[i].col, newB[j].col)) {
                case -1: /* go to next term in a */
                    i++; 
                    break;
                case 0: /* add terms, go to next term in a and b */
                    sum = (a[i++].value * newB[j++].value);
                    break;
                case 1: /* advance to next term in b*/
                    j++;
            }
        } /* end of for j <= totalb+1 */
        for (; a[i].row == row; i++)
            ;
        rowBegin = i; row = a[i].row;
    } /* end of for i <=totala */
    d[0].row = rowsA; /* a[0].row*/
    d[0].col = colsB; /* b[0].cols*/
    d[0].value = totalD;
} 

