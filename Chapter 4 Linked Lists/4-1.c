#include <stdio.h>
#include <stdlib.h> /* Random correlation function */
#include <string.h>

// Inserting and deleting nodes in a list

// self-referential structure                       
struct listNode {                                      
   char data; // each listNode contains a character 
   struct listNode *nextPtr; // pointer to next node
};                     
typedef struct listNode ListNode; // synonym for struct listNode
typedef ListNode *ListNodePtr; // synonym for ListNode*

// prototypes
void insert( ListNodePtr *sPtr, char value );
char delete( ListNodePtr *sPtr, char value );
int isEmpty( ListNodePtr sPtr );
void printList( ListNodePtr currentPtr );
void instructions( void );

int main( void ){ 
   ListNodePtr startPtr = NULL; // initially there are no nodes
   unsigned int choice; // user's choice
   char item; // char entered by user

   instructions(); // display the menu
   printf( "%s", "? " );
   scanf( "%u", &choice );

   // loop while user does not choose 3
   while ( choice != 3 ) { 

      switch ( choice ) { 
         case 1:
            printf( "%s", "Enter a character: " );
            scanf( "\n%c", &item );
            insert( &startPtr, item ); // insert item in list
            printList( startPtr );
            break;
         case 2: // delete an element
            // if list is not empty
            if ( !isEmpty( startPtr ) ) { 
               printf( "%s", "Enter character to be deleted: " );
               scanf( "\n%c", &item );

               // if character is found, remove it
               if ( delete( &startPtr, item ) ) { // remove item
                  printf( "%c deleted.\n", item );
                  printList( startPtr );
               } 
               else {
                  printf( "%c not found.\n\n", item );
               } 
            } 
            else {
               puts( "List is empty.\n" );
            } 
            break;
         default:
            puts( "Invalid choice.\n" );
            instructions();
            break;
      } 

      printf( "%s", "? " );
      scanf( "%u", &choice );
   }

   puts( "End of run." );
} 

// display program instructions to user
void instructions( void ){ 
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} 

// insert a new value into the list in sorted order
void insert( ListNodePtr *sPtr, char value ){ 
   ListNodePtr newPtr; // pointer to new node
   ListNodePtr previousPtr; // pointer to previous node in list
   ListNodePtr currentPtr; // pointer to current node in list
   newPtr = malloc( sizeof( ListNode ) ); // create node
   if ( newPtr != NULL ) { // is space available
      newPtr->data = value; // place value in node
      newPtr->nextPtr = NULL; // node does not link to another node
      previousPtr = NULL;
      currentPtr = *sPtr;
      // loop to find the correct location in the list       
      while ( currentPtr != NULL && value > currentPtr->data ) {
         previousPtr = currentPtr; // walk to ...               
         currentPtr = currentPtr->nextPtr; // ... next node 
      }                                      
      if ( previousPtr == NULL ) { // insert new node at beginning of list
         newPtr->nextPtr = *sPtr;
         *sPtr = newPtr;
      }
      else { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
         newPtr->nextPtr = currentPtr;
      }
   }
   else {
      printf( "%c not inserted. No memory available.\n", value );
   }
}

// delete a list element
char delete( ListNodePtr *sPtr, char value ){ 
   ListNodePtr previousPtr; // pointer to previous node in list
   ListNodePtr currentPtr; // pointer to current node in list
   ListNodePtr tempPtr; // temporary node pointer
   if ( value == ( *sPtr )->data ) { // delete first node
      tempPtr = *sPtr; // hold onto node being removed
      *sPtr = ( *sPtr )->nextPtr; // de-thread the node
      free( tempPtr ); // free the de-threaded node
      return value;
   } 
   else { 
      previousPtr = *sPtr;
      currentPtr = ( *sPtr )->nextPtr;
      // loop to find the correct location in the list
      while ( currentPtr != NULL && currentPtr->data != value ) { 
         previousPtr = currentPtr; // walk to ...  
         currentPtr = currentPtr->nextPtr; // ... next node  
      }
      if ( currentPtr != NULL ) {  // delete node at currentPtr
         tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
         free( tempPtr );
         return value;
      }
   }
   return '\0';
} 

// return 1 if the list is empty, 0 otherwise
int isEmpty( ListNodePtr sPtr ){ 
   return sPtr == NULL;
} // end function isEmpty

// print the list
void printList( ListNodePtr currentPtr ){ 
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty.\n" );
   } 
   else { 
      puts( "The list is:" );

      // while not the end of the list
      while ( currentPtr != NULL ) { 
         printf( "%c --> ", currentPtr->data );
         currentPtr = currentPtr->nextPtr;   
      }

      puts( "NULL\n" );
   }
} 