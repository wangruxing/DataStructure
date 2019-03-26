#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */
#include <string.h>

#define COMPARE(x, y) ((x < y) ? -1: (x == y)? 0: 1)
// Polynomial Addition - data structure 2

#define MAX_TERMS 100
typedef struct {
    float coef;
    int expon;
} polynomial;
polynomial terms[MAX_TERMS];
int avail = 6;

void padd(int, int, int, int, int, int);
void attach(float, int);

int main(void) {
    /*
    A(X)=2(X^1000)+1
    B(X)=X^4+10X^3+3X^2+1
    */
    terms[0].coef = 2;
    terms[0].expon = 1000;
    terms[1].coef = 1;
    terms[1].expon = 0;
    terms[2].coef = 1;
    terms[2].expon = 4;
    terms[3].coef = 10;
    terms[3].expon = 3;
    terms[4].coef = 3;
    terms[4].expon = 2;
    terms[5].coef = 1;
    terms[5].expon = 0;
    
    padd(0,1,2,5,0,0);
    printf("i    \t");
    for(int i = 0;i < 11;i++){
        printf("%2d\t", i);
    }
    printf("\ncoef \t");
    for(int i = 0;i < 11;i++){
        printf("%2.0f\t", terms[i].coef);
    }
    printf("\nexpon\t");
    for(int i = 0;i < 11;i++){
        printf("%2d\t", terms[i].expon);
    }
    return 0;
}

void padd (int starta, int finisha, int startb, int finishb,int startd, int finishd){
    float coefficient;
    startd = avail;
    while (starta <= finisha && startb <= finishb){
        switch (COMPARE(terms[starta].expon,terms[startb].expon)) {
            case -1: 
                attach(terms[startb].coef, terms[startb].expon);
                startb++;
                break;
            case 0: 
                coefficient = terms[starta].coef + terms[startb].coef;
                if (coefficient){
                    attach (coefficient, terms[starta].expon);
                    starta++;
                    startb++;
                }   
                break;
            case 1:
                attach(terms[starta].coef, terms[starta].expon);
                starta++;
        }
    }
    /* add in remaining terms of A(x) */
    for( ; starta <= finisha; starta++){
        attach(terms[starta].coef, terms[starta].expon);
    }    
    /* add in remaining terms of B(x) */
    for( ; startb <= finishb; startb++){
        attach(terms[startb].coef, terms[startb].expon);
        finishd =avail -1;
    }     
}

void attach(float coefficient, int exponent){
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "Too many terms in the polynomial\n");
        exit(1);
    }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}