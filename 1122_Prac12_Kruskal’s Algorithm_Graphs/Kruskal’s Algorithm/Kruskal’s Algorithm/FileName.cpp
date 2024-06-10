#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node
{
	char u;
	char v;
	int data;
};

int main() {

	FILE* fptr = fopen("Graph.txt", "r");
	node n[50][50] = {};
	node ans[50] = {};
	int count, c = 0;
	fscanf(fptr, "%d", &count);
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			fscanf(fptr, "%d", &n[i][j].data);
			if (j > i && n[i][j].data > 0) {
				ans[c].u = 'A' + i;
				ans[c].v = 'A' + j;
				ans[c].data = n[i][j].data;
				c++;
			}
		}
	}
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (ans[j].data > ans[i].data) {
				node temp = ans[j];
				ans[j] = ans[i];
				ans[i] = temp;
			}
		}
	}
	printf("Sorted:\n");
	for (int i = 0; i < c; i++)
	{
		printf("%c %c %d\n", ans[i].u, ans[i].v, ans[i].data);
	}
	printf("\n");
	int a_count = 0, total = 0;
	char char_Array[50][50] = {};
	char temp[3] = {};
	for (int i = 0; i < c; i++)
	{
		int Judge[2][2] = {};
		for (int j = 0; j < a_count; j++)
		{
			for (int k = 0; k < strlen(char_Array[j]); k++)
			{
				if (char_Array[j][k] == ans[i].u) {
					//temp[0] = ans[i].u;
					Judge[0][0]++;
					Judge[1][0] = j;
				}
				if (char_Array[j][k] == ans[i].v) {
					//temp[1] = ans[i].v;
					Judge[0][1]++;
					Judge[1][1] = j;
				}
			}
		}
		if (Judge[0][0] == 0 && Judge[0][1] == 0) {
			char_Array[a_count][strlen(char_Array[a_count])] = ans[i].u;
			char_Array[a_count][strlen(char_Array[a_count])] = ans[i].v;
			printf("%c %c %d\n", ans[i].u, ans[i].v, ans[i].data);
			a_count++;
			total += ans[i].data;
		}
		if (Judge[0][0] == 1 && Judge[0][1] == 0) {
			char_Array[Judge[1][0]][strlen(char_Array[Judge[1][0]])] = ans[i].v;
			printf("%c %c %d\n", ans[i].u, ans[i].v, ans[i].data);
			total += ans[i].data;
		}
		if (Judge[0][0] == 0 && Judge[0][1] == 1) {
			char_Array[Judge[1][1]][strlen(char_Array[Judge[1][1]])] = ans[i].u;
			printf("%c %c %d\n", ans[i].u, ans[i].v, ans[i].data);
			total += ans[i].data;
		}
		if (Judge[0][0] == 1 && Judge[0][1] == 1 && Judge[1][0] != Judge[1][1]) {
			strcat(char_Array[Judge[1][0]], char_Array[Judge[1][1]]);
			memset(char_Array[Judge[1][1]], 0, 50);
			printf("%c %c %d\n", ans[i].u, ans[i].v, ans[i].data);
			total += ans[i].data;
		}

	}

	printf("Minimum cost: %d", total);
}