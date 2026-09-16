//Given a directed graph G(V,E) and the starting Vertex 's'. Determine 
// 1. the lengths of the shortest paths from the starting vertex ‘s’ to all other vertices in the graph G using Dijkstra’s Algorithm.
// 2. Display the shortest path from the given source 's' to all other vertices. 
#include <stdio.h>
struct NODE{
    int vertex;
    int distance;
};
/* Swap two nodes */
int swap(struct NODE *a, struct NODE *b){
    struct NODE temp = *a;
    *a = *b;
    *b = temp;
    return 0;
}
/* Min-Heapify */
int heapify(struct NODE pq[], int n, int i){
    int smallest, left, right;
    smallest = i;
    left = 2 * i + 1;
    right = 2 * i + 2;
    if (left < n &&
        pq[left].distance < pq[smallest].distance)
        smallest = left;
    if (right < n &&
        pq[right].distance < pq[smallest].distance)
        smallest = right;
    if (smallest != i){
        swap(&pq[i], &pq[smallest]);
        heapify(pq, n, smallest);
    }
    return 0;
}

/* Insert into Min-Priority Queue */
int insert(struct NODE pq[], int *n, int vertex, int distance){
    int i, parent;
    i = *n;
    pq[i].vertex = vertex;
    pq[i].distance = distance;
    (*n)++;
    while (i > 0){
        parent = (i - 1) / 2;
        if (pq[parent].distance <= pq[i].distance)
            break;
        swap(&pq[parent], &pq[i]);
        i = parent;
    }
    return 0;
}
/* Delete minimum */
struct NODE deleteMin(struct NODE pq[], int *n){
    struct NODE min;
    min = pq[0];
    pq[0] = pq[*n - 1];
    (*n)--;
    if (*n > 0)
        heapify(pq, *n, 0);
    return min;
}
/* Display shortest path recursively */
int printPath(int parent[], int vertex){
    if (parent[vertex] == -1){
        printf("%d", vertex + 1);
        return 0;
    }
    printPath(parent, parent[vertex]);
    printf("->%d", vertex + 1);
    return 0;
}
/* Dijkstra's Algorithm */
int dijkstra(int graph[100][100], int n, int source){
    struct NODE pq[10000];
    struct NODE node;
    int distance[100];
    int parent[100];
    int visited[100];
    int size = 0;
    int i, j;
    /* Initialization */
    for (i = 0; i < n; i++){
        distance[i] = -1;
        parent[i] = -1;
        visited[i] = 0;
    }
    distance[source] = 0;
    insert(pq, &size, source, 0);
    /* Dijkstra */
    while (size > 0){
        node = deleteMin(pq, &size);
        i = node.vertex;
        if (visited[i])
            continue;
        visited[i] = 1;
        for (j = 0; j < n; j++){
            if (graph[i][j] != 0 && !visited[j]){
                if (distance[j] == -1 ||
                    distance[i] + graph[i][j] < distance[j]){
                    distance[j] =
                        distance[i] + graph[i][j];

                    parent[j] = i;

                    insert(pq, &size,
                           j, distance[j]);
                }
            }
        }
    }
    /* Display result */
    printf("\nSource\tDestination\tCost\tPath\n");
    for (i = 0; i < n; i++){
        printf("%d\t%d\t\t", source + 1, i + 1);
        if (distance[i] == -1){
            printf("Not Reachable\t-\n");
        }
        else{
            printf("%d\t\t", distance[i]);

            if (i == source)
                printf("-\n");
            else{
                printPath(parent, i);
                printf("\n");
            }
        }
    }

    return 0;
}
int main(){
    FILE *fp;
    int graph[100][100];
    int n, source;
    int i, j;
    fp = fopen("inDiAdjMat1.dat", "r");
    if (fp == NULL){
        printf("Error opening input file.\n");
        return 0;
    }
    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);
    /* Read adjacency matrix */
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++)
            fscanf(fp, "%d", &graph[i][j]);
    }
    fclose(fp);
    printf("Enter the Source Vertex: ");
    scanf("%d", &source);
    source--;
    dijkstra(graph, n, source);
    return 0;
}