#include<stdio.h>
#include<stdlib.h>

int recursion(int n) {
	if (n == 0) {
		return 0;
	}
	else if (n == 1) {
		return 1;
	}
	else {
		return recursion(n - 1) + recursion(n - 2);
	}
}



int main() {
	int n = 0;
	printf("input n:");
	scanf("%d", &n);

	printf("»¼°j:");
	for (int i = 0; i <= n; i++)
	{
		printf("%d ", recursion(i));
	}
	printf("\n");

	printf("°j°é:");
	int a[1000] = {};
	for (int i = 0; i <= n; i++)
	{
		if (i <= 1) {
			a[i] = i;
			printf("%d ", i);
		}
		else {
			int j = i;
			a[i] = a[j - 1] + a[j - 2];
			printf("%d ", a[j - 1] + a[j - 2]);
		}

	}

	printf("\n");
	return 0;
}