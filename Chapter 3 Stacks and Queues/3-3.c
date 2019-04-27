#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

// Implementation circular queue
int items[SIZE];
int front = -1, rear =-1;

int isEmpty();
int isFull();
void enQueue(int element);
int deQueue();
void printQueue();
void instructions(void);

int main(void) {
    unsigned int choice;
    int value;

    instructions();
    printf("%s", "? ");
    scanf("%u", &choice);

    while(choice != 3){
        switch (choice){
            case 1:
                printf("%s", "Enter an integer: ");
                scanf("%d", &value);
                enQueue(value);
                break;
            case 2:
                if(!isEmpty()){
                    printf("Deleted element -> %d \n", deQueue());
                    printQueue();
                }    
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
    "1 to add an item to the circle queue\n"
    "2 to remove an item to the circle queue\n"
    "3 to end program");
}

// Return 1 if the queue is empty, 0 otherwise
int isEmpty(){
    return front == -1;
}

int isFull(){
    return ((front == rear + 1) || (front == 0 && rear == SIZE-1));
}

void enQueue(int element){
    if(isFull()) {
        printf("Queue is full!! \n");
    }
    else{
        if(front == -1){
            front = 0;
        }
        rear = (rear + 1) % SIZE;
        items[rear] = element;
        printQueue();
    }
}

int deQueue(){
    int element;
    if(isEmpty()) {
        printf("Queue is empty !! \n");
        return(-1);
    } else {
        element = items[front];
        if (front == rear){
            front = -1;
            rear = -1;
        } 
        else {
            front = (front + 1) % SIZE;  
        }
        return(element);
    }
}

void printQueue(){
    int i;
    if(isEmpty()){
        printf("Empty Queue\n");
    }
    else{
        printf(" Front -> %d ",front);
        printf("\n Items -> ");
        for( i = front; i!=rear; i=(i+1)%SIZE){
            printf("%d ",items[i]);
        }
        printf("%d ",items[i]);
        printf("\n Rear -> %d \n",rear);
    }
}