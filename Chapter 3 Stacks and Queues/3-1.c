#include <stdio.h>
#include <stdlib.h> /* Random correlation function */

// Implementation stack
struct stackNode{
    int data;
    struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

void push(StackNodePtr *topPtr, int info);
int pop(StackNodePtr *topPtr);
int isEmpty(StackNodePtr topPtr);
void PrintStack(StackNodePtr currentPtr);
void instructions(void);


int main(void) {
    StackNodePtr stackPtr = NULL;
    unsigned int choice;
    int value;

    instructions();
    printf("%s", "? ");
    scanf("%u", &choice);

    while(choice != 3){
        switch(choice){
            case 1:
                printf("%s", "Enter an integer: ");
                scanf("%d", &value);
                push(&stackPtr, value);
                PrintStack(stackPtr);
                break;
            case 2:
                if(!isEmpty(stackPtr)){
                    printf("The popped value is %d.\n", pop(&stackPtr));
                }
                PrintStack(stackPtr);
                break;
            default:
                puts("Invalid choice.\n");
                instructions();
                break;
        }
        printf("%s", "? ");
        scanf("%u", &choice);
    }
    puts("End of run.");
}

// Display interface to user
void instructions(void){
    puts("Enter choice:\n"
    "1 to push a value on the stack\n"
    "2 to pop a value off the stack\n"
    "3 to end program");
}

// Insert a node at the top of the stack
void push(StackNodePtr *topPtr, int info){
    StackNodePtr newPtr;
    newPtr = malloc(sizeof(StackNode));

    if(newPtr != NULL){
        newPtr->data = info;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    }
    else{
        printf("%d not inserted. No memory available.\n", info);
    }
}

// Remove a node from the top of stack
int pop(StackNodePtr *topPtr){
    StackNodePtr tempPtr;
    int popValue;

    tempPtr = *topPtr;
    popValue = (*topPtr)->data;
    *topPtr = (*topPtr)->nextPtr;
    free(tempPtr);
    return popValue;
}

// Print satck
void PrintStack(StackNodePtr currentPtr){
    if(currentPtr == NULL){
        puts("The stack is empty.\n");
    }
    else{
        puts("The stack is:");

        while(currentPtr != NULL){
            printf("%d --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }
        puts("NULL\n");
    }
}

// Return 1 if the stack is empty, 0 otherwise
int isEmpty(StackNodePtr topPtr){
    return topPtr == NULL;
}