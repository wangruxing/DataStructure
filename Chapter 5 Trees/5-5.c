#include <stdio.h>
#include <stdlib.h> /* Random correlation function */
#include <time.h>   /* Time correlation function */
#include <string.h>
#define MAX_QUEUE_SIZE 100
#define COMPARE(x, y) ((x < y) ? -1: (x == y)? 0: 1)
#define MALLOC(p, s) \
    if(!((p) = malloc(s))){ \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }

/*
插入時 輸出levelOrder時會跑不出結果，但inorder正常 - 20190722 18:49
levelOrder錯誤已修正 - 20190722 19:20
 */
// self-referential structure                            
struct treeNode {                                           
   struct treeNode *leftPtr; // pointer to left subtree 
   int data; // node value                               
   struct treeNode *rightPtr; // pointer to right subtree
}; // end structure treeNode    


typedef struct treeNode TreeNode; // synonym for struct treeNode
typedef TreeNode *TreeNodePtr; // synonym for TreeNode*

void insertNode( TreeNodePtr *treePtr, int value );
TreeNodePtr searchNode(TreeNodePtr treePtr, int key);
void instructions(void);

void inOrder(TreeNodePtr treePtr);
void levelOrder(TreeNodePtr treePtr);
void queueFull();
void addq(TreeNodePtr treePtr);
TreeNodePtr deleteq();
TreeNodePtr rootPtr = NULL; // tree initially empty
int front = 0; 
int rear = 0;
TreeNodePtr queue[MAX_QUEUE_SIZE];
// Binary Search Tree
int main(void) {
    unsigned int i; // counter to loop from 1-10
    int item; // variable to hold random values
    int num;
    puts( "How many node in this tree: " );
    scanf("%d", &num);

    // insert random values between 0 and 14 in the tree
    printf( "Please input %d value: ", num );
    for ( i = 1; i <= num; ++i ) { 
        scanf("%d", &item);
        insertNode( &rootPtr, item );
    } // end for

    printf("inorder: ");
    inOrder(rootPtr);
    printf("\n");

    unsigned int choice;
    int value;
    int key;
    instructions();
    printf("%s", "? ");
    scanf("%u", &choice);
    
    while(choice != 3){
        switch(choice){
            case 1: // insert
                printf("%s", "Enter an integer: ");
                scanf("%d", &value);
                insertNode( &rootPtr, value );
                printf("inorder: ");
                inOrder(rootPtr);
                printf("\n");
                printf("levelorder: ");
                levelOrder(rootPtr);
                printf("\n");
                break;
            case 2: // search
                printf("%s", "What integer you want to search: ");
                scanf("%d", &key);
                searchNode(rootPtr, key);
                break;
            default: // end
                puts("Invalid choice.\n");
                instructions();
                break;
        }
        printf("%s", "? ");
        scanf("%u", &choice);
    }
    puts("End of run.");
    
    return 0;
}

// insert node into tree (binary search tree)
void insertNode( TreeNodePtr *treePtr, int value ){ 
   // if tree is empty
   if ( *treePtr == NULL ) {   
      *treePtr = malloc( sizeof( TreeNode ) );

      // if memory was allocated, then assign data
      if ( *treePtr != NULL ) { 
         ( *treePtr )->data = value;
         ( *treePtr )->leftPtr = NULL;
         ( *treePtr )->rightPtr = NULL;
      } // end if
      else {
         printf( "%d not inserted. No memory available.\n", value );
      } // end else
   } // end if
   else { // tree is not empty
      // data to insert is less than data in current node
      if ( value < ( *treePtr )->data ) {                   
         insertNode( &( ( *treePtr )->leftPtr ), value );   
      } // end if                                        

      // data to insert is greater than data in current node
      else if ( value > ( *treePtr )->data ) {                 
         insertNode( &( ( *treePtr )->rightPtr ), value );     
      } // end else if                                      
      else { // duplicate data value ignored
         printf( "%s", "dup" );
      } // end else
   } // end else
} // end function insertNode

// Display interface to user
void instructions(void){
    puts("Enter choice:\n"
    "1 to insert a value to the binary search tree\n"
    "2 to search binary search tree\n"
    "3 to end program");
}

// search node
TreeNodePtr searchNode(TreeNodePtr treePtr, int key){
    if(!treePtr){
        printf("Not in tree!!\n");
        return NULL;
    }
    else if(key == treePtr->data){
        printf("treePtr->data = %d\n", treePtr->data);
        return treePtr;
    }
    else if(key < treePtr->data)
        return searchNode(treePtr->leftPtr, key);
    return searchNode(treePtr->rightPtr, key);
}

// begin inorder traversal of tree
void inOrder( TreeNodePtr treePtr ){ 
   // if tree is not empty, then traverse
   if ( treePtr != NULL ) {                
      inOrder( treePtr->leftPtr );         
      printf( "%3d", treePtr->data );      
      inOrder( treePtr->rightPtr );        
   } // end if                          
} // end function inOrder

void levelOrder(TreeNodePtr treePtr){
    front = 0; 
    rear = 0;
    if(!treePtr) 
        return;
    addq(treePtr);
    for(;;){
        treePtr = deleteq();
        if(treePtr){
            printf("%3d", treePtr->data);
            if(treePtr->leftPtr)
                addq(treePtr->leftPtr);
            if(treePtr->rightPtr)
                addq(treePtr->rightPtr);
        }
        else break;
    }
}

void addq(TreeNodePtr treePtr){
    if(rear == MAX_QUEUE_SIZE-1)
        queueFull();
    queue[++rear] = treePtr;
}

TreeNodePtr deleteq(){
    return queue[++front];
}

void queueFull(){
    fprintf(stderr, "Queue is full, cannot add element");
    exit(EXIT_FAILURE);
}

