#include<stdio.h>
#include<stdlib.h>

int count = 0;

void example_1(int n, char A, char B, char C) {
	if (n == 1) {
		printf("%d, 盤子從%c移到%c\n", n, A, C);
		count++;
	}
	else {
		example_1(n - 1, A, C, B);
		printf("%d, 盤子從%c移到%c\n", n, A, C);
		count++;
		example_1(n - 1, B, A, C);
	}
}
int main() {
	int n;
	printf("請輸入n:");
	scanf("%d", &n);
	example_1(n, 'A', 'B', 'C');

	printf("數量:%d", count);
	return 0;
}