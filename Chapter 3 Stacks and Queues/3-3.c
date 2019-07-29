#include <stdio.h>
#include <stdlib.h>
#include <time.h>   /* Time correlation function */
#define MAX_STACK_SIZE 100
#define MAP_LENGTH 6
#define MAP_WIDTH 6
#define EXIT_ROW MAP_LENGTH-2
#define EXIT_COL MAP_WIDTH-2

// A Mazing Problem
// Walking directions
typedef struct {
    short int vert;
    short int horiz;
}offsets;
offsets move[8];

// Record path
typedef struct {
    short int row;
    short int col;
    short int dir;
}element;
element stack[MAX_STACK_SIZE];
element position;

void initMap();
void printMap(int row, int col);
void path(void);
element pop();
void stackFull();
void stackEmpty();
void push(element position);

short int top = -1;
int map[MAP_LENGTH][MAP_WIDTH];
int mark[MAP_LENGTH][MAP_WIDTH];
char resultMap[MAP_LENGTH][MAP_WIDTH];

int main(void) {
    initMap();
    path();
    return 0;
}

void initMap(){
    srand( time(NULL) );
    for(int i = 0;i < MAP_LENGTH;i++){
        for(int j = 0;j < MAP_WIDTH;j++){
            if(i == 0 || j == 0 || i == MAP_LENGTH-1 || j == MAP_WIDTH-1){
                map[i][j] = 1;
                mark[i][j] = 1;
                resultMap[i][j] = '1';
            }else{
                map[i][j] = rand() % 2;
                resultMap[i][j] = map[i][j] + '0';
                mark[i][j] = 0;
            }
        }
    }
    // init starting point and ending point
    map[1][1] = 0; // starting point
    resultMap[1][1] = '0';
    map[EXIT_ROW][EXIT_COL] = 0; // ending point
    resultMap[EXIT_ROW][EXIT_COL] = '0';

    move[0].vert = -1;
    move[0].horiz = 0;
    move[1].vert = -1;
    move[1].horiz = 1;
    move[2].vert = 0;
    move[2].horiz = 1;
    move[3].vert = 1;
    move[3].horiz = 1;
    move[4].vert = 1;
    move[4].horiz = 0;
    move[5].vert = 1;
    move[5].horiz = -1;
    move[6].vert = 0;
    move[6].horiz = -1;
    move[7].vert = -1;
    move[7].horiz = -1; 
}

void path(void){
    int row, col, nextRow, nextCol, dir, found=0;
    mark[1][1] = 1;
    top = 0;
    stack[0].row = 1;
    stack[0].col = 1;
    stack[0].dir = 1;
    while(top > -1 && !found){
        position = pop();
        row = position.row;
        col = position.col;
        dir = position.dir;
        while(dir < 8 && !found){
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            if(nextRow == EXIT_ROW && nextCol == EXIT_COL)
                found = 1;
            else if (!map[nextRow][nextCol] && !mark[nextRow][nextCol]){
                mark[nextRow][nextCol] = 1;
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                push(position);
                row = nextRow;
                col = nextCol;
                dir = 0;
            }
            else
                dir++;
        }
    }
    if(found){
        printMap(row, col);
    }
    else
        printf("The maze does not have path\n");
}

void printMap(int row, int col){
    printf("map\n");
    for(int i = 0;i < MAP_LENGTH;i++){
        for(int j = 0;j < MAP_WIDTH;j++){
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }

    printf("\nThe path is: \n");
    for(int k = 0;k <= top;k++){ 
        resultMap[stack[k].row][stack[k].col] = '*';
        printf("row=%d, col=%d\n", stack[k].row, stack[k].col);
        for(int i = 0;i < MAP_LENGTH;i++){
            for(int j = 0;j < MAP_WIDTH;j++){
                printf("%c ", resultMap[i][j]);
            }
            printf("\n");
        }  
        printf("\n");
        system("pause");
    }

    printf("row=%d, col=%d\n", row, col);
    resultMap[row][col] = '*';
    for(int i = 0;i < MAP_LENGTH;i++){
        for(int j = 0;j < MAP_WIDTH;j++){
            printf("%c ", resultMap[i][j]);
        }
        printf("\n");
    }  
    printf("\n");
    system("pause");

    printf("row=%d, col=%d\n", EXIT_ROW, EXIT_COL);
    resultMap[EXIT_ROW][EXIT_COL] = '*';
    for(int i = 0;i < MAP_LENGTH;i++){
        for(int j = 0;j < MAP_WIDTH;j++){
            printf("%c ", resultMap[i][j]);
        }
        printf("\n");
    }  
}

void stackFull(){
    fprintf(stderr, "Stack is full, cannot add element");
    exit(EXIT_FAILURE);
}

void stackEmpty(){
    fprintf(stderr, "Stack is empty, cannot pop element");
    exit(EXIT_FAILURE);
}

element pop(){
    if(top == -1)
        stackEmpty();
    return stack[top--];
}

void push(element position){
    if(top >= MAX_STACK_SIZE-1)
        stackFull();
    stack[++top] = position;
}