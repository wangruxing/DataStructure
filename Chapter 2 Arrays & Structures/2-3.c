#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */
#include <string.h>

// Self-Referential Structures
typedef struct {
    char data;
    struct list *link;
} list;
list item1, item2, item3;
int main(void) {
    // create node
    item1.data='a';
    // --------
    // | a |  | 
    // --------
    item2.data='b';
    // --------      --------
    // | a |  |      | b |  | 
    // --------      --------
    item3.data='c';
    // --------      --------      --------
    // | a |  |      | b |  |      | c |  |
    // --------      --------      --------

    // create link
    item1.link=item2.link=item3.link=NULL;
    // --------      --------      --------
    // | a |  |----->| b |  |----->| c |  |----->NULL
    // --------      --------      --------
    return 0;
}