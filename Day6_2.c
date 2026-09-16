//Given an undirected weighted connected graph G(V, E). Apply Krushkal’s algorithm to
// 1. Find the minimum spanning tree T(V, E’) and Display the selected edges of G.
// 2. Display total cost of the minimum spanning tree T.

#include <stdio.h>
struct EDGE{
    int u;
    int v;
    int weight;
};
/* Swap two edges */
int swap(struct EDGE *a, struct EDGE *b){
    struct EDGE temp = *a;
    *a = *b;
    *b = temp;
    return 0;
}
/* Min-Heapify based on edge weight */
int heapify(struct EDGE a[], int n, int i){
    int smallest, left, right;
    smallest = i;
    left = 2 * i + 1;
    right = 2 * i + 2;
    if (left < n &&
        a[left].weight < a[smallest].weight)
        smallest = left;
    if (right < n &&
        a[right].weight < a[smallest].weight)
        smallest = right;
    if (smallest != i){
        swap(&a[i], &a[smallest]);
        heapify(a, n, smallest);
    }
    return 0;
}
/* Heap Sort */
int heapSort(struct EDGE a[], int n){
    int i;
    /* Build Min-Heap */
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
    /* Sort */
    for (i = n - 1; i > 0; i--){
        swap(&a[0], &a[i]);
        heapify(a, i, 0);
    }
    return 0;
}
/* Find parent of a vertex */
int find(int parent[], int x)
{
    if (parent[x] == x)
        return x;
    return find(parent, parent[x]);
}
/* Union two sets */
int unionSet(int parent[], int rank[], int x, int y){
    int rootX, rootY;
    rootX = find(parent, x);
    rootY = find(parent, y);
    if (rootX == rootY)
        return 0;
    if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else if (rank[rootX] > rank[rootY])
        parent[rootY] = rootX;
    else{
        parent[rootY] = rootX;
        rank[rootX]++;
    }
    return 1;
}

/* Kruskal's Algorithm */
int kruskal(struct EDGE edges[], int n, int m){
    int parent[100];
    int rank[100];
    int i;
    int count = 0;
    int total = 0;
    for (i = 0; i < n; i++){
        parent[i] = i;
        rank[i] = 0;
    }
    printf("\nEdge\tCost\n");
    for (i = 0; i < m && count < n - 1; i++){
        if (unionSet(parent, rank,
                     edges[i].u - 1,
                     edges[i].v - 1)){
            printf("%d--%d\t%d\n",
                   edges[i].u,
                   edges[i].v,
                   edges[i].weight);
            total += edges[i].weight;
            count++;
        }
    }
    return total;
}
int main(){
    FILE *fp;
    struct EDGE edges[100];
    int n, m;
    int i;
    int total;
    fp = fopen("inKruskal.dat", "r");
    if (fp == NULL){
        printf("Error opening input file.\n");
        return 0;
    }
    fscanf(fp, "%d %d", &n, &m);
    for (i = 0; i < m; i++){
        fscanf(fp, "%d %d %d",
               &edges[i].u,
               &edges[i].v,
               &edges[i].weight);
    }
    fclose(fp);
    /* Sort edges by increasing weight */
    heapSort(edges, m);
    total = kruskal(edges, n, m);
    printf("\nTotal Weight of the Spanning Tree: %d\n",
           total);
    return 0;
}