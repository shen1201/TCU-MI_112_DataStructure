#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int u, v, weight;
} Edge;

typedef struct {
    int parent;
    int rank;
} Subset;

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void selectionSort(Edge arr[], int n) {
    int i, j, min_idx;

    // 移動陣列邊界
    for (i = 0; i < n - 1; i++) {
        // 找出剩餘陣列中的最小元素
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j].weight < arr[min_idx].weight) {
                min_idx = j;
            }
        }
        // 交換找到的最小元素與第一個元素
        Edge temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

void printf_all(Edge edges[], int e) {
    printf("所有相連的邊:\n");
    printf("point1 point2 cost\n");
    for (int i = 0; i < e; i++) {
        printf("%d\t%d\t%d\n", edges[i].u, edges[i].v, edges[i].weight);
    }
    selectionSort(edges, e);
    printf("所有相連的邊:\n");
    printf("point1 point2 cost\n");
    for (int i = 0; i < e; i++) {
        printf("%d\t%d\t%d\n", edges[i].u, edges[i].v, edges[i].weight);
    }
}

void KruskalMST(int graph[MAX][MAX], int V) {
    int i, e = 0;
    Edge edges[MAX];

    for (i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph[i][j] != 0) {
                edges[e].u = i;
                edges[e].v = j;
                edges[e].weight = graph[i][j];
                e++;
            }
        }
    }

    printf_all(edges, e);

    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));
    for (i = 0; i < V; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    Edge result[MAX];
    int k = 0, totalWeight = 0;

    for (i = 0; i < e; i++) {
        int u = find(subsets, edges[i].u);
        int v = find(subsets, edges[i].v);

        if (u != v) {
            result[k++] = edges[i];
            totalWeight += edges[i].weight;
            Union(subsets, u, v);
        }
    }

    printf("\nKruskal算法選擇的邊:\n");
    printf("point1 point2 cost\n");
    for (i = 0; i < k; i++)
        printf("%d\t%d\t%d\n", result[i].u, result[i].v, result[i].weight);
    printf("total weight = %d\n", totalWeight);

    free(subsets);
}




int main() {
    FILE* file = fopen("Graph.txt", "r");
    if (!file) {
        printf("Cannot open file.\n");
        return 1;
    }

    int V;
    fscanf(file, "%d", &V);
    int graph[MAX][MAX];

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);

    KruskalMST(graph, V);

    return 0;
}
