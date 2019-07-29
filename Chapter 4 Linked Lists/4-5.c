#include <stdio.h>
#include <stdlib.h> /* Random correlation function */
#include <time.h>   /* Time correlation function */
#include <string.h>

#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1
#define MALLOC(p, s) \
    if(!((p) = malloc(s))){ \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }

// self-referential structure                       
struct node {                                      
   char data; // each listNode contains a character 
   struct node *link; // pointer to next node
};                     
typedef struct node Node; // synonym for struct node
typedef Node *NodePtr; // synonym for Node*

// Equivalence Relations
int main(void) {
    short int out[MAX_SIZE];
    NodePtr seq[MAX_SIZE];
    NodePtr x, y, top;
    int i, j, n;

    printf("Enter the size (<= %d) ", MAX_SIZE);
    scanf("%d", &n);
    for(i = 0;i < n;i++){
        out[i] = TRUE;
        seq[i] = NULL;
    }

    // Phase 1: Input the equivalence pairs
    printf("Enter a pair of numbers (-1 -1 to quit): ");
    scanf("%d%d", &i, &j);
    while(i >= 0){
        MALLOC(x, sizeof(*x));
        x->data = j;
        x->link = seq[i];
        seq[i] = x;
        MALLOC(x, sizeof(*x));
        x->data = i;
        x->link = seq[j];
        seq[j] = x;
        printf("Enter a pair of numbers (-1 -1 to quit): ");
        scanf("%d%d", &i, &j);
    }

    // Phase 2: Output the equivalence classes
    for(i = 0;i < n;i++){
        if(out[i]){
            printf("\nNew class: %5d", i);
            out[i] = FALSE;
            x = seq[i];
            top = NULL;
            for(;;){
                while(x){
                    j = x->data;
                    if(out[j]){
                        printf("%5d", j);
                        out[j] = FALSE;
                        y = x->link; 
                        x->link = top; 
                        top = x; 
                        x = y; 
                    }
                    else{
                        x = x->link;
                    }
                }
                if(!top)
                    break;
                x = seq[top->data];
                top = top->link;
            }
        }
    }
    return 0;
}