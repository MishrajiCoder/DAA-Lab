//Given an undirected weighted connected graph G(V,E) and starring vertex 's'. Maintain a Min-Priority Queue 'Q' from the vertex set V and apply Prim's Algorithm to
// 1. Find the minimum spanning tree T(V,E'). Display the cost adjancey matrix of 'T'
// 2. Display the cost of minimum spanning tree T.

#include <stdio.h>
struct NODE{
    int vertex;
    int key;
};
/* Swapping between two nodes */
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
    if (left < n && pq[left].key < pq[smallest].key)
        smallest = left;
    if (right < n && pq[right].key < pq[smallest].key)
        smallest = right;
    if (smallest != i){
        swap(&pq[i], &pq[smallest]);
        heapify(pq, n, smallest);
    }
    return 0;
}
/* Insert into Min-Priority Queue */
int insert(struct NODE pq[], int *n, int vertex, int key){
    int i, parent;
    i = *n;
    pq[i].vertex = vertex;
    pq[i].key = key;
    (*n)++;
    while (i > 0){
        parent = (i - 1) / 2;
        if (pq[parent].key <= pq[i].key)
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
/* Display Matrix */
int display(int a[100][100], int n){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
    return 0;
}
/* Prim's Algorithm */
int prim(int graph[100][100], int mst[100][100],
         int n, int start){
    struct NODE pq[10000];
    struct NODE node;
    int key[100];
    int parent[100];
    int visited[100];
    int size = 0;
    int i, j;
    int total = 0;
    /* Initialization */
    for (i = 0; i < n; i++){
        key[i] = 0;
        parent[i] = -1;
        visited[i] = 0;
        for (j = 0; j < n; j++)
            mst[i][j] = 0;
    }
    /* Starting vertex */
    insert(pq, &size, start, 0);
    while (size > 0){
        node = deleteMin(pq, &size);
        i = node.vertex;
        if (visited[i])
            continue;
        visited[i] = 1;
        for (j = 0; j < n; j++){
            if (graph[i][j] != 0 && !visited[j])
            {
                if (parent[j] == -1 ||
                    graph[i][j] < key[j]){
                    key[j] = graph[i][j];
                    parent[j] = i;
                    insert(pq, &size, j, key[j]);
                }
            }
        }
    }
    /* Create MST */
    for (i = 0; i < n; i++){
        if (parent[i] != -1){
            mst[i][parent[i]] = graph[i][parent[i]];
            mst[parent[i]][i] = graph[i][parent[i]];
            total = total + graph[i][parent[i]];
        }
    }
    return total;
}
int main(){
    FILE *fp;
    int graph[100][100];
    int mst[100][100];
    int n, start;
    int i, j;
    int total;
    fp = fopen("inUnAdjMat.dat", "r");
    if (fp == NULL){
        printf("Error opening file.\n");
        return 0;
    }
    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++)
            fscanf(fp, "%d", &graph[i][j]);
    }
    fclose(fp);
    printf("Enter the Starting Vertex: ");
    scanf("%d", &start);
    start = start - 1;
    total = prim(graph, mst, n, start);
    printf("\nCost Adjacency Matrix of Minimum Spanning Tree:\n");
    display(mst, n);
    printf("\nTotal Weight of the Spanning Tree: %d\n", total);
    return 0;
}