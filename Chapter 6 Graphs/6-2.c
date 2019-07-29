#include<stdio.h>
#include<stdlib.h>
#define VAL 999

// Kruskal’s Algorithm
int i,j,k,a,b,u,v,n,ne=1;
int min,mincost=0,cost[9][9],parent[9];
int visited[10]= {
	0
};
// union - find 
int find(int i){
    while(parent[i])
    i=parent[i];
    return i;
}
int uni(int i,int j){
    if(i!=j){
        parent[j]=i;
        return 1;
    }
    return 0;
}
int main(){ 
    printf("Implementation of Kruskal's algorithm\n");
    printf("Enter the no. of vertices:");
    scanf("%d",&n);
    printf("Enter the cost adjacency matrix:\n");
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            scanf("%d",&cost[i][j]);
            if(cost[i][j]==0)
                cost[i][j]=VAL;
        }
    }
    printf("\nThe edges of Minimum Cost Spanning Tree are\n");
    while(ne < n){
        for(i=1,min=VAL;i<=n;i++){
            for(j=1;j <= n;j++){
                if(cost[i][j] < min){
                    min=cost[i][j];
                    a=u=i;
                    b=v=j;
                }
            }
        }
        u=find(u);
        v=find(v);
        if(uni(u,v)){
            // printing edges
            printf("%d edge (%d,%d) =%d\n",ne++,a,b,min);
            mincost +=min;
        }
        cost[a][b]=cost[b][a]=VAL;
    }
    // minimum cost
    printf("\nMinimum cost = %d\n",mincost);
    return 0;
}

/* input
Enter the no. of vertices:7
Enter the cost adjacency matrix:
0 12 0 0 0 35 0
12 0 24 0 0 0 25
0 24 0 32 0 0 0
0 0 32 0 10 0 22
0 0 0 10 0 15 18
35 0 0 0 15 0 0
0 25 0 22 18 0 0
 */

/*output
The edges of Minimum Cost Spanning Tree are
1 edge (4,5) =10
2 edge (1,2) =12
3 edge (5,6) =15
4 edge (5,7) =18
5 edge (2,3) =24
6 edge (2,7) =25

Minimum cost = 104
 */