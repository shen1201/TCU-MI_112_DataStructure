#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// �w�q�`�I���c
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// �w�q�ϵ��c
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* inDegree; // �J�׼Ʋ�
} Graph;

// �Ыظ`�I
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// �Ыع�
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

// �K�[��
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    graph->inDegree[dest]++; // �W�[�ؼг��I���J��
}

// �ݼ��Ƨ�
void topologicalSort(Graph* graph) {
    int* inDegree = graph->inDegree;
    int* stack = (int*)malloc(graph->numVertices * sizeof(int));
    int top = 0;

    // �N�Ҧ��J�׬�0�����I�[�J���|
    for (int i = 0; i < graph->numVertices; i++) {
        if (inDegree[i] == 0) {
            stack[top++] = i;
        }
    }

    // �M�����|
    while (top > 0) {
        int v = stack[--top];
        printf("%d ", v); // ��X���I

        // �M���۾F�`�I�ô�֨�J��
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
    FILE* file = fopen("0613��J�d��.txt", "r");
    if (!file) {
        fprintf(stderr, "�L�k���}���\n");
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

    printf("�ݼ��Ƨǵ��G�G\n");
    topologicalSort(graph);

    return 0;
}
