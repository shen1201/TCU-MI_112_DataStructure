#include<stdio.h>
#include<stdlib.h>

int isCompleteGraph(int Matrix[100][100], int n);
int isConnectedGraph(int Matrix[100][100], int n);
int isConnectedComponent(int Matrix[100][100], int n);
void DFS(int Matrix[][100], int* Visit, int node, int n);

int main() {
	FILE* fp;
	fp = fopen("01.txt", "r");
	int M[100][100] = {};
	int n = 0;
	fscanf(fp, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			fscanf(fp, "%d", &M[i][j]);
		}
	}

	printf("adjacency matrix:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", M[i][j]);
		}
		printf("\n");
	}
	if (isCompleteGraph(M, n)) {
		printf("a complete graph\n");
	}
	else {
		printf("not a complete graph\n");
	}

	if (isConnectedGraph(M, n)) {
		printf("a connected graph\n");
	}
	else {
		printf("not a connected graph\n");
	}

	int x = isConnectedComponent(M, n);
	printf("%d connected components\n", x);

	fclose(fp);
	return 0;
}

int isCompleteGraph(int Matrix[100][100], int n) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i != j && Matrix[i][j] == 0) {
				return 0;
			}
		}
	}
	return 1;
}

int isConnectedGraph(int Matrix[100][100], int n) {
	int visit[100] = {};

	DFS(Matrix, visit, 0, n);

	for (int i = 0; i < n; i++)
	{
		if (!visit[i]) {
			return 0;
		}
	}
	return 1;
}

void DFS(int Matrix[][100], int* visit, int node, int n) {
	visit[node] = 1;
	for (int i = 0; i < n; i++)
	{
		if (Matrix[node][i] == 1 && visit[i] != 1) {
			DFS(Matrix, visit, i, n);
		}
	}
}

int isConnectedComponent(int Matrix[100][100], int n) {
	int visit[100] = {};
	int count = 0;

	for (int i = 0; i < n; i++)
	{
		if (!visit[i]) {
			DFS(Matrix, visit, i, n);
			count++;
		}
	}
	return count;
}