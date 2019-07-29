#include <stdio.h>
#include <stdlib.h> 

// Implementation queue
struct queueNode{
    char data;
    struct queueNode *nextPtr;
};
typedef struct queueNode QueueNode; // synonym for struct queueNode
typedef QueueNode *QueueNodePtr;    // synonym for QueueNode*

void printQueue(QueueNodePtr currentPtr);
int isEmpty(QueueNodePtr headPtr);
char dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr);
void enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, char value);
void instructions(void);

int main(void) {
    QueueNodePtr headPtr = NULL;
    QueueNodePtr tailPtr = NULL;
    unsigned int choice;
    char item;

    instructions();
    printf("%s", "? ");
    scanf("%u", &choice);

    while(choice != 3){
        switch (choice){
            case 1:
                printf("%s", "Enter a character: ");
                scanf("\n%c", &item);
                enqueue(&headPtr, &tailPtr, item);
                printQueue(headPtr);
                break;
            case 2:
                if(!isEmpty(headPtr)){
                    item = dequeue(&headPtr, &tailPtr);
                    printf("%c has been dequeued.\n", item);
                }
                printQueue(headPtr);
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
    "1 to add an item to the queue\n"
    "2 to remove an item to the queue\n"
    "3 to end program");
}

// insert a item at the tail of the queue
void enqueue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr, char value){
    QueueNodePtr newPtr;
    newPtr = malloc(sizeof(QueueNode));
    if(newPtr != NULL){
        newPtr->data = value;
        newPtr->nextPtr = NULL;
        if(isEmpty(*headPtr)){
            *headPtr = newPtr;             // the queue is empty
        }else{                  
            (*tailPtr)->nextPtr = newPtr;  // the queue isn't empty
        }
        *tailPtr = newPtr;
    }
    else{
        printf("%c not inserted. No memory available.\n", value);
    }
}

// Remove a item from the head of queue
char dequeue(QueueNodePtr *headPtr, QueueNodePtr *tailPtr){
    char value;
    QueueNodePtr tempPtr;
    value = (*headPtr)->data;
    tempPtr = *headPtr;
    *headPtr = (*headPtr)->nextPtr;
    if(*headPtr == NULL){
        *tailPtr = NULL;
    }
    free(tempPtr);
    return value;
}

// Return 1 if the queue is empty, 0 otherwise
int isEmpty(QueueNodePtr headPtr){
    return headPtr == NULL;
}

// Print queue
void printQueue(QueueNodePtr currentPtr){
    if(currentPtr == NULL){
        puts("Queue is empty.\n");
    }
    else{
        puts("The queue is: ");
        while(currentPtr != NULL){
            printf("%c --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }
        puts("NULL\n");
    }
}
