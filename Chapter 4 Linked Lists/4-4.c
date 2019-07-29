#include <stdio.h>
#include <stdlib.h> /* Random correlation function */
#define COMPARE(x, y) ((x < y) ? -1: (x == y)? 0: 1)
#define MALLOC(p, s) \
    if(!((p) = malloc(s))){ \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
// Algorithm for Adding Polynomials

struct polyNode{
    int coef;
    int expon;
    struct polyNode *link;
} ;
typedef struct polyNode PolyNode; // synonym for struct polyNode
typedef PolyNode *PolyNodePtr; // synonym for PolyNode*
PolyNodePtr a, b;

void insert( PolyNodePtr *sPtr, int c, int e );
void printPoly( PolyNodePtr currentPtr );
PolyNodePtr padd(PolyNodePtr a, PolyNodePtr b);
void attach(float coefficient, int exponent, PolyNodePtr *ptr);

void insert(PolyNodePtr *sPtr, int c, int e){ 
    PolyNodePtr newPtr; // pointer to new node
    PolyNodePtr previousPtr; // pointer to previous node
    PolyNodePtr currentPtr; // pointer to current node

    MALLOC(newPtr, sizeof(*newPtr)); // create node
    if ( newPtr != NULL ) { // is space available
        newPtr->coef = c; // place coef in node
        newPtr->expon = e; // place expon in node
        newPtr->link = NULL; // node does not link to another node

        previousPtr = NULL;
        currentPtr = *sPtr;

        // loop to find the correct location in the list       
        while ( currentPtr != NULL && e < currentPtr->expon ) {
            previousPtr = currentPtr; // walk to ...               
            currentPtr = currentPtr->link; // ... next node 
        } // end while                                         

        // insert new node at beginning of list
        if ( previousPtr == NULL ) { 
            newPtr->link = *sPtr;
            *sPtr = newPtr;
        } // end if
        else { // insert new node between previousPtr and currentPtr
            previousPtr->link = newPtr;
            newPtr->link = currentPtr;
        } // end else
    } // end if
    else {
        printf( "%c not inserted. No memory available.\n", e );
    } // end else
} // end function insert

void printPoly( PolyNodePtr currentPtr ){ 
    // while not the end of the list
    while ( currentPtr != NULL ) { 
        printf( "%d, %d --> ", currentPtr->coef, currentPtr->expon);
        currentPtr = currentPtr->link;   
    } // end while

    puts( "NULL\n" );
} // end function printPoly

PolyNodePtr padd(PolyNodePtr a, PolyNodePtr b){
    PolyNodePtr c, rear, temp;
    int sum;
    MALLOC(rear, sizeof(*rear));
    c = rear;
    while(a && b){
        switch(COMPARE(a->expon, b->expon)){
            case -1:  // a->expon < b->expon
                attach(b->coef, b->expon, &rear);
                b = b->link;
                break;
            case 0:   // a->expon = b->expon
                sum = a->coef + b->coef;
                if (sum)
                    attach(sum, a->expon, &rear);
                a = a->link;
                b = b->link;
            case 1:   // a->expon > b->expon
                attach(a->coef, a->expon, &rear);
                a = a->link;
        }
    }
    // copy rest of list a and then list b
    for(; a; a = a->link)
        attach(a->coef, a->expon, &rear);
    for(; b; b = b->link)
        attach(b->coef, b->expon, &rear);
    rear->link = NULL;
    // delete extra initial node
    temp = c;
    c = c->link;
    free(temp);
    return c;
}

void attach(float coefficient, int exponent, PolyNodePtr *ptr){
    PolyNodePtr temp;
    MALLOC(temp, sizeof(*temp));
    temp->coef = coefficient;
    temp->expon = exponent;
    (*ptr)->link = temp;
    *ptr = temp;
}

int main(void) {
    int numA, numB;
    int e, c;
    // create polynomial a
    printf("%s", "Number of terms of polynomial a:");
    scanf("\n%d", &numA);
    PolyNodePtr a = NULL;
    for(int i = 0;i < numA;i++){
        printf("\nEnter term %d coef, expon respectively\n", i+1);
        scanf( "\n%d", &c );
        scanf( "\n%d", &e );
        insert( &a, c, e ); // insert coef and expon in polynomial a
    }

    // create polynomial b
    printf( "%s", "Number of terms of polynomial b:" );
    scanf( "\n%d", &numB );
    PolyNodePtr b = NULL;
    for(int i = 0;i < numB;i++){
        printf("\nEnter term %d coef, expon respectively\n",i+1);
        scanf( "\n%d", &c );
        scanf( "\n%d", &e );
        insert( &b, c, e ); // insert coef and expon in polynomial b
    }

    // print polynomial
    puts( "Polynomial a:" );
    printPoly( a );
    puts( "Polynomial b:" );
    printPoly( b );

    // print result
    puts( "Polynomial c:" );
    printPoly( padd(a, b) );
    return 0;
}