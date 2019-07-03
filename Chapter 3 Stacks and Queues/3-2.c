#include <stdio.h>
#include <stdlib.h> /* Random correlation function */
#include <time.h>   /* Time correlation function */
#include <string.h>

#define MAX_QUEUE_SIZE 100 /* maximum stack size */

// Implementation stack by array
int stack[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

int isEmpty();
int enqueue(int rear, int value); 
int dequeue(int rear, int front);

int main(int argc, char *argv[]) {
	int value;
	int i;
    printf("Current front = %d, rear = %d\n", front, rear);
	printf("Please enter 10 data in sequence:\n");
	for(i=0;i<10;i++){
		scanf("%d",&value);
		rear = enqueue(rear, value);
        printf("Current queue: ");
        for(int j = front+1;j <= rear;j++){
            printf("%d ", stack[j]);
        }
        printf(". front = %d, rear = %d\n", front, rear);
	}
	printf("====================\n");
    printf("The queue dequeue sequence is: \n"); 
	while(!isEmpty()){
		front = dequeue(rear, front); 
        printf("Current queue: ");
        for(int j = front+1;j <= rear;j++){
            printf("%d ", stack[j]);
        }
        printf(". front = %d, rear = %d\n\n", front, rear);
	}
	return 0;
}

int isEmpty(){
	if(rear == front){
		return 1; 
	}else{
		return 0;
	}
} 

int enqueue(int rear, int value){
	if(rear == MAX_QUEUE_SIZE){
		printf("Queue is full.\n");	
	}else{
		rear++;
		stack[rear] = value;
	}
    return rear;
} 

int dequeue(int rear, int front){
	int value;
	if(isEmpty()){
		printf("Queue is empty.\n");
	}else{
        front++;
		value = stack[front];
        printf("dequeue value = %d\n",value); 
		return front; 
	}
}