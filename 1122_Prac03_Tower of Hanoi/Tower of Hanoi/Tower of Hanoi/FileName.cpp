#include<stdio.h>
#include<stdlib.h>

int count = 0;

void example_1(int n, char A, char B, char C) {
	if (n == 1) {
		printf("%d, �L�l�q%c����%c\n", n, A, C);
		count++;
	}
	else {
		example_1(n - 1, A, C, B);
		printf("%d, �L�l�q%c����%c\n", n, A, C);
		count++;
		example_1(n - 1, B, A, C);
	}
}
int main() {
	int n;
	printf("�п�Jn:");
	scanf("%d", &n);
	example_1(n, 'A', 'B', 'C');

	printf("�ƶq:%d", count);
	return 0;
}