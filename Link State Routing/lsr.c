#include <stdio.h>
#include <limits.h>

void main()
{
    int  i, j, n, d, source, adj[50][50];
    int dist[50], visited[50], round, v;
    int min, min_index;
    printf("How many nodes ? : ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix\n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            scanf("%d", &adj[i][j]);
        }
    }

    //set all distance to INT_MAX and visited to 0
    for(i=0; i<n; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    printf("Enter the source node: ");
    scanf("%d", &source);  // User selects the source node
    dist[source] = 0;   //distance from source to source is 0
    for(round = 0; round < n - 1; round++)
    {
        min = INT_MAX;
        for(v = 0; v<n; v++)
        {
            //finding link with minimum distance
            if(visited[v] == 0 && dist[v] < min)
            {
                min = dist[v];
                min_index = v;
            }
        }
        visited[min_index] = 1;
        for(d=0; d<n; d++)
        {
            if(!visited[d] && adj[min_index][d] && dist[min_index] != INT_MAX && dist[min_index] + adj[min_index][d] < dist[d])
            {
                dist[d] = dist[min_index] + adj[min_index][d];
            }
        }
    }
    printf("\nVertex distance from source\n");
    for(i=0; i<n; i++)
    {
        if (dist[i] == INT_MAX)
        {
            printf("%d\t\tINF\n", i);
        }
        else
        {
            printf("%d\t\t%d\n",i,dist[i]);
        }
    }
}