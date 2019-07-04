#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_QUEUE_SIZE 100
// Creating and traversing a binary tree 
// preorder, inorder, postorder and levelorder

// self-referential structure                            
struct treeNode {                                           
   struct treeNode *leftPtr; // pointer to left subtree 
   int data; // node value                               
   struct treeNode *rightPtr; // pointer to right subtree
}; // end structure treeNode                             

typedef struct treeNode TreeNode; // synonym for struct treeNode
typedef TreeNode *TreeNodePtr; // synonym for TreeNode*

// prototypes
void insertNode( TreeNodePtr *treePtr, int value );
void inOrder( TreeNodePtr treePtr );
void preOrder( TreeNodePtr treePtr );
void postOrder( TreeNodePtr treePtr );
void levelOrder( TreeNodePtr treePtr );
void queueFull();
void queueEmpty();
void addq(TreeNodePtr treePtr);
TreeNodePtr deleteq();
int front = 0; 
int rear = 0;
TreeNodePtr queue[MAX_QUEUE_SIZE];

// function main begins program execution
int main( void ){ 
   unsigned int i; // counter to loop from 1-10
   int item; // variable to hold random values
   TreeNodePtr rootPtr = NULL; // tree initially empty
    
   srand( time( NULL ) ); 
   puts( "The numbers being placed in the tree are:" );

   // insert random values between 0 and 14 in the tree
   for ( i = 1; i <= 10; ++i ) { 
      item = rand() % 15;
      printf( "%3d", item );
      insertNode( &rootPtr, item );
   } // end for

   // traverse the tree preOrder
   puts( "\n\nThe preOrder traversal is:" );
   preOrder( rootPtr );

   // traverse the tree inOrder
   puts( "\n\nThe inOrder traversal is:" );
   inOrder( rootPtr );

   // traverse the tree postOrder
   puts( "\n\nThe postOrder traversal is:" );
   postOrder( rootPtr );

   // traverse the tree levelOrder
   puts( "\n\nThe levelOrder traversal is:" );
   levelOrder( rootPtr );
} // end main

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

// begin inorder traversal of tree
void inOrder( TreeNodePtr treePtr ){ 
   // if tree is not empty, then traverse
   if ( treePtr != NULL ) {                
      inOrder( treePtr->leftPtr );         
      printf( "%3d", treePtr->data );      
      inOrder( treePtr->rightPtr );        
   } // end if                          
} // end function inOrder

// begin preorder traversal of tree
void preOrder( TreeNodePtr treePtr ){ 
   // if tree is not empty, then traverse
   if ( treePtr != NULL ) {                
      printf( "%3d", treePtr->data );      
      preOrder( treePtr->leftPtr );        
      preOrder( treePtr->rightPtr );       
   } // end if                          
} // end function preOrder

// begin postorder traversal of tree
void postOrder( TreeNodePtr treePtr ){ 
   // if tree is not empty, then traverse
   if ( treePtr != NULL ) {                
      postOrder( treePtr->leftPtr );       
      postOrder( treePtr->rightPtr );      
      printf( "%3d", treePtr->data );      
   } // end if                          
} // end function postOrder

void levelOrder(TreeNodePtr treePtr){
    if(!treePtr) return;
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

void queueEmpty(){
    fprintf(stderr, "Queue is empty, cannot delete element");
    exit(EXIT_FAILURE);
}