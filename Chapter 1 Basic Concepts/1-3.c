#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */

# define MAX_SIZE 5
// Program 1.17: Matrix addition with count statements   29
int main(void) {
    int i, j;
    int rows, cols;
    int count = 0;
    printf("Enter array rows: ");
    scanf("%d", &rows);
    printf("Enter array cols: ");
    scanf("%d", &cols);
    int a[rows][cols], b[rows][cols], c[rows][cols];
    for(i = 0;i < rows; i++){
        count++;
        printf("\"for(i = 0;i < rows; i++)\", i=%d, count=%d\n", i, count);
        for(j = 0;j < cols; j++){
            count++;
            printf("\"for(j = 0;j < cols; j++)\", j=%d, count=%d\n", j, count);
            c[i][j] = a[i][j] + b[i][j];
            count++;
            printf("\"c[i][j] = a[i][j] + b[i][j];\", count=%d\n", count);
        }
        count++;
        printf("last time of j for loop, count=%d\n", count);
    }
    count++;
    printf("last time of i for loop, count=%d\n", count);
    return 0;
}
