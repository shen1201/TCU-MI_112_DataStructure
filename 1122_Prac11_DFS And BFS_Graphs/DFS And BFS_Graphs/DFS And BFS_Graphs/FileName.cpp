#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    struct Node* adjLists[100];
    int visited[100];
};

void matrixToList(int matrix[100][100], struct Graph* graph, int size);
void addEdge(struct Graph* graph, int src, int dest);
struct Node* createNode(int v);
void printGraph(struct Graph* graph, int size);
struct Graph* createGraph(int size);
void DFS(struct Graph* graph, int vertex);
void BFS(struct Graph* graph, int startVertex);
void resetVisited(struct Graph* graph, int size);

int main() {
    FILE* fp = fopen("InputData.txt", "r");

    if (fp == NULL) {
        printf("無法打開文件\n");
        return 1;
    }

    int array[100][100] = { 0 };
    int size = 0;
    fscanf(fp, "%d", &size);
    struct Graph* graph = createGraph(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fscanf(fp, "%d", &array[i][j]);
        }
    }
    fclose(fp);

    printf("矩陣:\n");
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            printf("%d ", array[i][k]);
        }
        printf("\n");
    }

    matrixToList(array, graph, size);

    printf("\n鄰接表:\n");
    printGraph(graph, size);

    printf("\n深度優先搜索 (DFS): ");
    DFS(graph, 0);
    printf("\n");

    resetVisited(graph, size);

    printf("廣度優先搜索 (BFS): ");
    BFS(graph, 0);
    printf("\n");

    return 0;
}

struct Graph* createGraph(int size) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

    for (int i = 0; i < size; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void matrixToList(int matrix[100][100], struct Graph* graph, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == 1) {
                addEdge(graph, i, j);
            }
        }
    }
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    if (graph->adjLists[src] == NULL) {
        graph->adjLists[src] = newNode;
    }
    else {
        struct Node* temp = graph->adjLists[src];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void printGraph(struct Graph* graph, int size) {
    for (int v = 0; v < size; v++) {
        struct Node* temp = graph->adjLists[v];
        printf("V%d: ", v);
        while (temp) {
            printf("-> V%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void DFS(struct Graph* graph, int vertex) {
    struct Node* adjList = graph->adjLists[vertex];
    struct Node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("V%d ", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void BFS(struct Graph* graph, int startVertex) {
    struct Node* adjList;
    struct Node* temp;

    int queue[100];
    int front = 0;
    int rear = 0;

    graph->visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front != rear) {
        int currentVertex = queue[front++];
        printf("V%d ", currentVertex);

        adjList = graph->adjLists[currentVertex];
        temp = adjList;

        while (temp) {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
}

void resetVisited(struct Graph* graph, int size) {
    for (int i = 0; i < size; i++) {
        graph->visited[i] = 0;
    }
}
