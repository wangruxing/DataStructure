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
// print ver.
// self-referential structure        
typedef struct node *nodePointer;
struct node{                                      
   char data; // each listNode contains a character 
   nodePointer link; // pointer to next node
};                     
//typedef struct node Node; // synonym for struct node
//typedef Node *NodePtr; // synonym for Node*

// Equivalence Relations
int main(void) {
    short int out[MAX_SIZE];
    nodePointer seq[MAX_SIZE];
    nodePointer x, y, top;
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
        printf("\ni=%d\n out[]=", i);
        for(j = 0;j < n;j++){
            printf("%d ", out[j]);
        }
        if(out[i]){
            printf("\nNew class: %5d", i);
            out[i] = FALSE;
            x = seq[i];
            top = NULL;
            for(;;){
                while(x){
                    j = x->data;
                    if(out[j]){
                        printf("out[%d]=%d\n", j, out[j]);
                        //printf("%5d\n", j);
                        out[j] = FALSE;
                        printf("before: ");
                        if(x)
                            printf("x = %d ", x->data);
                        else
                            printf("x = NULL ");
                        if(y)
                            printf("y = %d ", y->data);
                        else
                            printf("y = NULL ");
                        if(top)
                            printf("top = %d", top->data);
                        else
                            printf("top = NULL");
                        printf("\n");
                        y = x->link; 
                        printf("y = x->link: \t");
                        if(y)
                            printf("y = %d ", y->data);
                        else
                            printf("y = NULL ");
                        printf("\n");
                        if(x->link)
                            printf("x->link = %d ", (x->link)->data);
                        else
                            printf("x->link = NULL ");
                        printf("\n");
                        x->link = top; 
                        printf("x->link = top: \t");
                        if(x->link)
                            printf("x->link = %d ", (x->link)->data);
                        else
                            printf("x->link = NULL ");
                        if(top)
                            printf("top = %d", top->data);
                        else
                            printf("top = NULL");
                        printf("\n");
                        top = x; 
                        printf("top = x: \t");
                        if(top)
                            printf("top = %d", top->data);
                        else
                            printf("top = NULL");
                        printf("\n");
                        x = y; 
                        printf("x = y: ");
                        if(x)
                            printf("x = %d ", x->data);
                        else
                            printf("x = NULL ");
                        printf("\n");
                        printf("after: ");
                        if(x)
                            printf("x = %d ", x->data);
                        else
                            printf("x = NULL ");
                        if(y)
                            printf("y = %d ", y->data);
                        else
                            printf("y = NULL ");
                        if(top)
                            printf("top = %d", top->data);
                        else
                            printf("top = NULL");
                        printf("\n\n");
                    }
                    else{
                        printf("out[%d]=%d\n", j, out[j]);
                        x = x->link;
                        printf("x = x->link: ");
                        if(x)
                            printf("x = %d", x->data);
                        else
                            printf("x = NULL");
                        printf("\n");

                    }
                }

                if(!top)
                    break;
                printf("over while!!\n");
                printf("before: ");
                if(x)
                    printf("x = %d ", x->data);
                else
                    printf("x = NULL ");
                if(top)
                    printf("top = %d", top->data);
                else
                    printf("top = NULL");
                printf("\n");
                x = seq[top->data];
                printf("x = seq[top->data]: ");
                if(x)
                    printf("x = %d ", x->data);
                else
                    printf("x = NULL ");
                printf("\n");
                top = top->link;
                printf("top = top->link: ");
                if(top)
                    printf("top = %d", top->data);
                else
                    printf("top = NULL");
                printf("\n");
            }
        }
    }
    return 0;
}