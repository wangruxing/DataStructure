#include <stdio.h>
#include <stdlib.h> /* Random correlation function */
#include <time.h>   /* Time correlation function */
#include <string.h>

// Threaded BT
struct threadedTree {                                            
   char data;                             
   struct threadedTree *rightChild; // pointer to right subtree
   short int rightThread;
   struct threadedTree *leftChild;  // pointer to left subtree 
   short int leftThread;
}; 
typedef struct threadedTree TreeNode; // synonym for struct threadedTree
typedef TreeNode *threadedPointer; // synonym for TreeNode*

// prototypes
threadedPointer insucc(threadedPointer tree);
void tinorder(threadedPointer tree);
void insertRight (threadedPointer s, threadedPointer r);
void insertLeft (threadedPointer s, threadedPointer l);

// Finding the inorder successor of a node
threadedPointer insucc(threadedPointer tree){
    threadedPointer temp;
    temp = tree->rightChild;
    if(!tree->rightThread)
        while(!temp->leftThread)
            temp = temp->leftChild;
    return temp;
}

// Inorder traversal of a threaded binary tree
void tinorder(threadedPointer tree){
    threadedPointer temp = tree;
    if ( temp != NULL ) { 
        for(;;){
            temp = insucc(temp);
            if(temp == tree) break;
            printf("%3c", temp->data);
        }
    }
    else{
        printf("NULL\n");
    }
}

void insertRight (threadedPointer s
                    , threadedPointer r){
    threadedPointer temp;
    r->rightChild = s->rightChild;
    r->rightThread = s->rightThread;
    r->leftChild = s;
    r->leftThread = 1;
    s->rightChild = r;
    s->rightThread = 0;
    if(!r->rightThread){
        temp = insucc(r);
        temp->leftChild = r;
    }
}

void insertLeft (threadedPointer s, threadedPointer l){
    threadedPointer temp;
    l->leftChild= s->rightChild;
    l->leftThread = s->rightThread;
    l->rightChild = s;
    l->rightThread = 0;
    s->leftChild = l;
    s->leftThread = 1;
    if(!l->leftThread){
        temp = insucc(l);
        temp->rightChild = l;
    }
}

int main(void) {

    return 0;
}