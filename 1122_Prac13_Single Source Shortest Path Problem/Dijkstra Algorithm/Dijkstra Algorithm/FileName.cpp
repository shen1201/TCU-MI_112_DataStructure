#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node {
    char site;
    int w;
    struct node* next;
};

struct node* create_root(int w, int v) {
    struct node* s = (struct node*)malloc(sizeof(struct node));
    s->site = ('A' + v);
    s->w = w;
    s->next = NULL;
    return s;
}

void root_direction(struct node* site, int w, int v) {
    struct node* current = site;
    struct node* s = (struct node*)malloc(sizeof(struct node));
    s->site = 'A' + v;
    s->w = w;
    s->next = NULL;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = s;
}

void print_graph(struct node* Site[], int size) {
    for (int i = 0; i < size; i++) {
        struct node* current = Site[i];
        while (current != NULL) {
            if (current->w != 0) {  // Avoid printing zero-weight edges
                printf("(%c-%c: %d)  ", 'A' + i, current->site, current->w);
            }
            current = current->next;
        }
        printf("\n");
    }
}

int min_distance(int dist[], int visited[], int size) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < size; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }

    return min_index;
}

void print_step(int dist[], int size, int parent[]) {
    for (int i = 0; i < size; i++) {
        if (dist[i] != INT_MAX) {
            printf("(%d,%c) ", dist[i], 'A' + i);
            int j = i;
            while (parent[j] != -1) {
                printf("(%d,%c) ", dist[parent[j]], 'A' + parent[j]);
                j = parent[j];
            }
        }
        else {
            printf("(-1,%c) ", 'A' + i);
        }
    }
    printf("\n");
}

void print_path(int parent[], int j) {
    if (parent[j] == -1) {
        printf("A");
        return;
    }
    print_path(parent, parent[j]);
    printf("->%c", 'A' + j);
}

void dijkstra(struct node* Site[], int size, int start) {
    int dist[100];
    int visited[100];
    int parent[100];

    for (int i = 0; i < size; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }
    dist[start] = 0;

    for (int count = 0; count < size - 1; count++) {
        int u = min_distance(dist, visited, size);
        if (u == -1) break; // all reachable nodes have been visited

        visited[u] = 1;

        struct node* current = Site[u];
        while (current != NULL) {
            int v = current->site - 'A';
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + current->w < dist[v]) {
                dist[v] = dist[u] + current->w;
                parent[v] = u;
            }
            current = current->next;
        }

        print_step(dist, size, parent);
    }

    // Print final paths and distances
    for (int i = 1; i < size; i++) {
        if (dist[i] != INT_MAX) {
            printf("A -> %c: %d, ", 'A' + i, dist[i]);
            print_path(parent, i);
            printf("\n");
        }
    }
}

int main() {
    int size = 0;
    FILE* fp = fopen("Data-1.txt", "r");
    if (fp == NULL) {
        printf("無法開啟檔案 Data-1.txt\n");
        return 1;
    }

    fscanf(fp, "%d", &size);
    struct node* Site[5] = { NULL };  // Initialize array to hold pointers to nodes

    int weight = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fscanf(fp, "%d", &weight);
            if (weight != -1) {
                if (Site[i] == NULL) {
                    Site[i] = create_root(weight, j);
                }
                else {
                    root_direction(Site[i], weight, j);
                }
            }
        }
    }

    fclose(fp);

    print_graph(Site, size);

    int start = 0; // Start vertex for Dijkstra's algorithm
    printf("Dijkstra's 演算法從頂點 %c 開始:\n", 'A' + start);
    dijkstra(Site, size, start);

    return 0;
}
