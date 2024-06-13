#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// 定義節點結構
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 定義圖結構
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* inDegree; // 入度數組
} Graph;

// 創建節點
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// 創建圖
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->inDegree = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->inDegree[i] = 0;
    }

    return graph;
}

// 添加邊
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    graph->inDegree[dest]++; // 增加目標頂點的入度
}

// 拓撲排序
void topologicalSort(Graph* graph) {
    int* inDegree = graph->inDegree;
    int* stack = (int*)malloc(graph->numVertices * sizeof(int));
    int top = 0;

    // 將所有入度為0的頂點加入堆疊
    for (int i = 0; i < graph->numVertices; i++) {
        if (inDegree[i] == 0) {
            stack[top++] = i;
        }
    }

    // 遍歷堆疊
    while (top > 0) {
        int v = stack[--top];
        printf("%d ", v); // 輸出頂點

        // 遍歷相鄰節點並減少其入度
        Node* temp = graph->adjLists[v];
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            inDegree[adjVertex]--;
            if (inDegree[adjVertex] == 0) {
                stack[top++] = adjVertex;
            }

            temp = temp->next;
        }
    }
    printf("\n");

    free(stack);
}

int main() {
    FILE* file = fopen("0613輸入範例.txt", "r");
    if (!file) {
        fprintf(stderr, "無法打開文件\n");
        exit(1);
    }

    int vertices;
    fscanf(file, "%d", &vertices);

    Graph* graph = createGraph(vertices);

    for (int i = 0; i < vertices; i++) {
        printf("V%d: ", i);
        for (int j = 0; j < vertices; j++) {
            int edge;
            fscanf(file, "%d", &edge);
            if (edge == 1) {
                printf("%d ", j);
                addEdge(graph, i, j);
            }
        }
        printf("\n");
    }

    fclose(file);

    printf("拓撲排序結果：\n");
    topologicalSort(graph);

    return 0;
}
