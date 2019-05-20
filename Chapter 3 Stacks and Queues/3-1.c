#include <stdio.h>
#include <stdlib.h> /* Random correlation function */
#include <time.h>   /* Time correlation function */
#include <string.h>

#define MAX_STACK_SIZE 100 /* maximum stack size */

// Implementation stack by array
int stack[MAX_STACK_SIZE];
int top = -1;

int isEmpty();
void push(int top); 
int pop();

int main(int argc, char *argv[]) {
	int value;
	int i;
    printf("Current top = %d\n", top);
	printf("Please enter 10 data in sequence:\n");
	for(i=0;i<10;i++){
		scanf("%d",&value);
		push(value);
        printf("Current stack: ");
        for(int j = 0;j <= top;j++){
            printf("%d ", stack[j]);
        }
        printf(". top = %d\n", top);
	}

	printf("============================================================\n");
    printf("The stack pop sequence is: \n"); 
	while(!isEmpty()){
		printf("pop value = %d\n",pop());
        printf("Current stack: ");
        for(int j = 0;j <= top;j++){
            printf("%d ", stack[j]);
        }
        printf(". top = %d\n\n", top);    
	}
    
	return 0;
}

int isEmpty(){
	if(top == -1){
		return 1; 
	}else{
		return 0;
	}
} 

void push(int data){
	if(top >= MAX_STACK_SIZE){
		printf("Stack is full.\n");	
	}else{
		top++;
		stack[top]=data;
	}
} 

int pop(){
	int data;
	if(isEmpty()){
		printf("Stack is empty.\n");
	}else{
		data=stack[top--];
		return data; 
	}
}

