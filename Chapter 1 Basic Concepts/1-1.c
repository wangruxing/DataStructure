#include <stdio.h>
#include <stdlib.h> /* Random correlation function */
#include <time.h>   /* Time correlation function */

// Program 1.13: Program 1.11 with count statements
int main(void) {
    int n = 5;
    printf("Loop execution times=%d\n", n);
    // Random seed
    srand( time(NULL) );
    // Random range
    int min = 1;
    int max = n+100;
    // Randomly generate integers
    int list[n];
    for(int i = 0;i < n;i++){
        list[i] = rand() % (max - min + 1) + min;
    }
    int count = 0;
    float tempsum = 0;
    count++;
    printf("\"float tempsum = 0;\", count=%d\n", count);
    int i;
    for(i = 0;i < n;i++){
        count++;
        printf("\"for(i = 0;i < n;i++)\",i=%d, count=%d\n", i, count);
        tempsum += list[i];
        count++;
        printf("\"tempsum += list[i];\", count=%d\n", count);
    }
    count++;
    printf("last execution of for, count=%d\n", count);
    count++;
    printf("\"return 0;\", count=%d\n", count);
    return 0;
}