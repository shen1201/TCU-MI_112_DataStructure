#include<stdio.h>
#include<stdlib.h>
#define Size 100
//struct Node {
// char start, goal;
// int weight;
// struct Node* ptr;
//};
//typedef struct Node* NodePtr;

void dijkstra(int read[Size][Size], int src, int size);
void printPath(int path[], int j);

int main() {
	FILE* fptr;
	int size, read[Size][Size], count = 0;
	//NodePtr adjacency[Size] = { NULL };

	fptr = fopen("Data-1.txt", "r");
	if (fptr == NULL) {
		printf("error");
		return 1;
	}
	fscanf(fptr, "%d", &size);
	read[size][size] = {};
	while (!feof(fptr)) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				fscanf(fptr, "%d", &read[i][j]);
			}
		}
	}
	fclose(fptr);

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%3d ", read[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	dijkstra(read, 0, size);//�u �X�o�I �j�p

	return 0;
}
void dijkstra(int read[Size][Size], int src, int size) {
	int dist[Size], visited[Size] = { 0 }, path[Size] = {}; // �ΨӦs��̵u�Z�� ���X���� ���|
	const int INF = 1000; //�L�k��F

	for (int i = 0; i < size; i++) {
		dist[i] = INF;
		path[i] = -1;
	}
	dist[src] = 0;//�X�o�IA

	for (int i = 0; i < size; i++) {
		int min = INF, min_index;//�̵u�Z�� �̵u�Z���I
		for (int j = 0; j < size; j++) {//�����X���`�I���Z���̪�
			if (visited[j] == 0 && dist[j] <= min) {
				min = dist[j];
				min_index = j;
			}
		}

		int u = min_index;
		visited[u] = 1;//�w���X

		// ��s��w�`�I���F�~���Z����
		for (int v = 0; v < size; v++) {
			if (visited[v] == 0 && read[u][v] > 0 && dist[u] != INF && dist[u] + read[u][v] < dist[v]) {
				//visited[v] == 0 v���Q�X��  read[u][v]>0 ����
				//dist[u] != INF �O�i�F��    dist[u] + read[u][v] < dist[v] �q�L u ��F v ��ثe�w�����̵u�Z����u
				dist[v] = dist[u] + read[u][v];
				path[v] = u;
				printf("(%d,%c) ", dist[v], u + 'A');
			}
			else {
				if (path[v] == -1) {
					if (dist[v] == INF) {
						printf("(-1,%c) ", v + 'A');
					}
					else {
						printf("(%d,%c) ", dist[v], v + 'A');
					}
				}
				else {
					printf("(%d,%c) ", dist[v], path[v] + 'A');
				}
			}
		}
		printf("\n");
	}

	printf("\nVertex Distanc Path\n");
	for (int i = 0; i < size; i++) {
		if (dist[i] == INF) {
			printf("%d \t INF\n", i);
		}
		else {
			printf("%c->%c: \t %d\t ", 'A', i + 'A', dist[i]);
			printPath(path, i);
			printf("\n");
		}
	}
}
void printPath(int path[], int j) {
	if (path[j] == -1) {
		printf("%c", j + 'A');
		return;
	}
	printPath(path, path[j]);
	printf(" -> %c", j + 'A');
}

/*
(A,0) (1,A) (5,A) (1,E)
(0,A) (8,D) (4,A) (7,D)
(0,A) (8,D) (3,A) (7,D)
(0,A) (8,D) (5,A) (7,D)
(0,A) (8,D) (5,A) (7,D)
*/
//https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/