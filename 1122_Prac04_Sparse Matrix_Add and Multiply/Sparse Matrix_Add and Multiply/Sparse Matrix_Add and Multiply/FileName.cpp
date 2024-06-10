#include<stdio.h>
#include<stdlib.h>


int main() {
	FILE* file;
	int A[100][3] = {}, B[100][3] = {}, C[100][100] = { 0 }, D[100][100] = { 0 };

	int A_arr[100][100] = { 0 }, B_arr[100][100] = { 0 };
	int A_count = 0, B_count = 0;
	char input;
	int number = 0;//判斷是不是0
	int count = 0;//計算第幾行
	file = fopen("1.txt", "r");
	if (file == NULL) {
		printf("無法打開\n");
		return 1;
	}

	while (!feof(file)) {
		fscanf(file, "%c", &input);
		if (input == 'A' || input == 'B') {
			if (input == 'A') {
				fscanf(file, "%d", &A_count);
				A[count][0] = A_count;
				A[count][1] = A_count;
				count++;
				for (int i = 0; i < A_count; i++)
				{
					for (int j = 0; j < A_count; j++)
					{
						fscanf(file, "%d", &number);
						if (number != 0) {
							A[count][0] = i;
							A[count][1] = j;
							A[count][2] = number;
							A[0][2] = count;
							count++;
						}
					}
				}
				count = 0;
			}
			if (input == 'B') {
				fscanf(file, "%d", &B_count);
				B[count][0] = B_count;
				B[count][1] = B_count;
				count++;
				for (int i = 0; i < B_count; i++)
				{
					for (int j = 0; j < B_count; j++)
					{
						fscanf(file, "%d", &number);
						if (number != 0) {
							B[count][0] = i;
							B[count][1] = j;
							B[count][2] = number;
							B[0][2] = count;
							count++;
						}
					}
				}
			}

		}

	}


	fclose(file);


	printf("A\n");
	for (int i = 1; i < A[0][2] + 1; i++)
	{
		A_arr[A[i][0]][A[i][1]] += A[i][2];
	}
	for (int i = 0; i < A_count; i++)
	{
		for (int j = 0; j < A_count; j++)
		{
			printf("%d\t", A_arr[i][j]);
		}
		printf("\n");
	}

	printf("\n");



	for (int i = 0; i < A[0][2] + 1; i++)
	{
		printf("%d\t%d\t%d\n", A[i][0], A[i][1], A[i][2]);
	}
	printf("\n");



	printf("B\n");
	for (int i = 1; i < B[0][2] + 1; i++)
	{
		B_arr[B[i][0]][B[i][1]] += B[i][2];
	}

	for (int i = 0; i < B_count; i++)
	{
		for (int j = 0; j < B_count; j++)
		{
			printf("%d\t", B_arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");


	for (int i = 0; i < B[0][2] + 1; i++)
	{
		printf("%d\t%d\t%d\n", B[i][0], B[i][1], B[i][2]);
	}
	for (int i = 1; i < A[0][2] + 1; i++)
	{
		C[A[i][0]][A[i][1]] += A[i][2];
	}
	for (int i = 1; i < B[0][2] + 1; i++)
	{
		C[B[i][0]][B[i][1]] += B[i][2];
	}


	printf("\n\nA+B:\n");
	for (int i = 0; i < A_count; i++)
	{
		for (int j = 0; j < A_count; j++)
		{
			printf("%d\t", C[i][j]);
		}
		printf("\n");
	}

	printf("\n\nA*B:\n");
	for (int i = 1; i < A[0][2] + 1; i++)
	{
		for (int j = 1; j < B[0][2] + 1; j++)
		{
			if (A[i][1] == B[j][0]) {
				D[A[i][0]][B[j][1]] += A[i][2] * B[j][2];
			}
		}
	}

	for (int i = 0; i < A_count; i++)
	{
		for (int j = 0; j < A_count; j++)
		{
			printf("%d\t", D[i][j]);
		}
		printf("\n");
	}

	return 0;
}