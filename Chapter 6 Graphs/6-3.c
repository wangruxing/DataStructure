#include<stdio.h>
#include<conio.h>
int a,b,u,v,n,i,j,ne=1;
int visited[10]= {0},min,mincost=0,cost[10][10];

// Prim’s Algorithm
void main() {
	printf("Enter the number of nodes:");
	scanf("%d",&n);
	printf("Enter the adjacency matrix:\n");
	for (i=1;i<=n;i++)
	  for (j=1;j<=n;j++) {
		scanf("%d",&cost[i][j]);
		if(cost[i][j]==0)
		    cost[i][j]=999;
	}
	visited[1]=1;
	printf("\nThe edges of Minimum Cost Spanning Tree are\n");
	while(ne<n) {
		for (i=1,min=999;i<=n;i++)
		   for (j=1;j<=n;j++)
		    if(cost[i][j]<min)
		     if(visited[i]!=0) {
			min=cost[i][j];
			a=u=i;
			b=v=j;
		}
		if(visited[u]==0 || visited[v]==0) {
			printf("Edge %d:(%d %d) cost:%d\n",ne++,a,b,min);
			mincost+=min;
			visited[b]=1;
		}
		cost[a][b]=cost[b][a]=999;
	}
	printf("\nMinimun cost=%d",mincost);
}
/* input
0 12 0 0 0 35 0
12 0 24 0 0 0 25
0 24 0 32 0 0 0
0 0 32 0 10 0 22
0 0 0 10 0 15 18
35 0 0 0 15 0 0
0 25 0 22 18 0 0
 */