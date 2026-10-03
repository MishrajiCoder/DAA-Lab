// Given a directed weighted graph G(V,E) where weight indicates distance. Vertices will be numbered consecutively from 1 to n(user input), and edges will have varying distances or lengths. 
// 1. Determine the length of the shortest path between every pair of vertices using Floyd's Warshall Algorithm 
// 2. Display the intermediate vertices on the shortest-path from the given pair of vertices(u,v). 

#include <stdio.h>
#define MAX 100

/* Print the shortest path */
int printPath(int next[MAX][MAX], int u, int v){
    if (next[u][v] == -1){
        printf("No path");
        return 0;
    }
    printf("%d", u + 1);
    while (u != v){
        u = next[u][v];
        printf("-->%d", u + 1);
    }
    return 0;
}

/* Floyd-Warshall Algorithm */
int floydWarshall(int graph[MAX][MAX],
                  int dist[MAX][MAX],
                  int next[MAX][MAX],
                  int n)
{
    int i, j, k;
    /* Initialize distance and next matrices */
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if (i == j){
                dist[i][j] = 0;
                next[i][j] = j;
            }
            else if (graph[i][j] != 0){
                dist[i][j] = graph[i][j];
                next[i][j] = j;
            }
            else{
                dist[i][j] = 99999;
                next[i][j] = -1;
            }
        }
    }

    /* Floyd-Warshall */
    for (k = 0; k < n; k++){
        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                if (dist[i][k] != 99999 &&
                    dist[k][j] != 99999 &&
                    dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] =
                        dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
    return 0;
}

/* Display shortest path matrix */
int displayMatrix(int dist[MAX][MAX], int n){
    int i, j;
    printf("\nShortest Path Weight Matrix:\n");
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if (dist[i][j] == 99999)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int main(){
    FILE *fp;
    int graph[MAX][MAX];
    int dist[MAX][MAX];
    int next[MAX][MAX];
    int n;
    int source, destination;
    int i, j;
    fp = fopen("inDiAdjMat2.dat", "r");
    if (fp == NULL){
        printf("Error opening input file.\n");
        return 0;
    }

    printf("Number of Vertices: ");
    scanf("%d", &n);
    /* Read adjacency matrix */
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++)
            fscanf(fp, "%d", &graph[i][j]);
    }

    fclose(fp);
    printf("Enter the source and destination vertex: ");
    scanf("%d %d", &source, &destination);
    source--;
    destination--;
    floydWarshall(graph, dist, next, n);
    displayMatrix(dist, n);
    printf("\nShortest Path from vertex %d to vertex %d: ",
           source + 1, destination + 1);
    printPath(next, source, destination);
    printf("\nPath weight: %d\n",
           dist[source][destination]);
    return 0;
}