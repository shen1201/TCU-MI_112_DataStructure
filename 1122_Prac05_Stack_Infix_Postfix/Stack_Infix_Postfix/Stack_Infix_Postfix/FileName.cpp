#include<stdio.h>
#include<string.h>
#include<ctype.h>

void prefix_Infix(char str[], char stack_1[]);
int Infix_prefix(char str[], char stack_1[]);
void postfix_Infix(char str[], char stack_1[]);
int Infix_postfix(char str[], char stack_1[]);
int main() {//Infix中序 prefix前序 postfix後序
	char str[20] = {}, stack_1[10] = {}, stack_2[10] = {}, eat = {};
	int choose = 0;
	while (choose != -1) {
		//printf("1.前序轉中序 2.後續轉中序 3.中序轉前序 4.中序轉後序 -1結束\n");
		printf("2.後續轉中序  4.中序轉後序 -1結束\n");
		printf("請輸入選擇:");
		scanf("%d%c", &choose, &eat);
		switch (choose)
		{
		case 1:
			printf("請輸入公式:");
			gets_s(str);
			prefix_Infix(str, stack_1);
			break;
		case 2:
			printf("請輸入公式:");
			gets_s(str);
			postfix_Infix(str, stack_1);
			break;
		case 3:
			printf("請輸入公式:");
			gets_s(str);
			Infix_prefix(str, stack_1);
			break;
		case 4:
			printf("請輸入公式:");
			gets_s(str);
			Infix_postfix(str, stack_1);
			break;
		case -1:

			break;
		default:
			printf("沒這選項\n");
			break;
		}
	}
	return 0;
}
void prefix_Infix(char str[], char stack_1[]) {
	char ans[10][20] = {};
	int top = 0;
	int count = 0;
	int counts = 0;
	int k = 0;

	int kk[2] = {};
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] >= 65 && str[i] <= 90) {
			kk[0]++;
		}
		else {
			kk[1]++;
		}
	}
	if (kk[0] - 1 == kk[1]) {
		for (int i = strlen(str) - 1; i != -1; i--)
		{
			if (str[i] >= 65 && str[i] <= 90 && counts > 0) {
				ans[top][0] = str[i];
				top++;
				counts--;
			}
			else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
				char string[10][10] = {};

				string[0][0] = str[i];
				strcat(ans[top - 1], string[0]);
				strcat(ans[top - 1], ans[top - 2]);
				strcat(ans[top - 1], ")");
				for (int j = strlen(ans[top - 1]); j != 0; j--)
				{
					ans[top - 1][j] = ans[top - 1][j - 1];
				}
				ans[top - 1][0] = '(';
				strcpy(ans[top - 2], ans[top - 1]);
				memset(ans[top - 1], 0, 100);
				count++;
				counts++;
				top--;
			}
			else {
				printf("公式錯誤\n");
				k++;
				break;//停掉for
			}
		}
		int cc[2] = {};
		int count_2 = 0;
		if (k == 0)
		{
			for (int i = 0; i < strlen(ans[0]); i++)
			{
				if (ans[0][i] == '(') {
					cc[0]++;
				}
				else if (ans[0][i] == ')') {
					cc[1]++;
				}
			}
			if (cc[0] == cc[1] && count * 2 == cc[0] + cc[1])
			{
				cc[0] = 1;
				for (int i = 0; i < strlen(ans[0]); i++)
				{
					if (ans[0][i] >= 65 && ans[0][i] <= 90) {
						if (cc[0] == 1) {
							cc[0] = 0;
						}
						else {
							count_2 = 1;
							break;
						}
					}
					else if (ans[0][i] == '+' || ans[0][i] == '-' || ans[0][i] == '*' || ans[0][i] == '/') {
						if (cc[0] == 0) {
							cc[0] = 1;
						}
						else {
							count_2 = 1;
							break;
						}
					}
				}
				if (count_2 == 0) {
					printf("%s\n", ans[0]);
				}
				else {
					printf("公式錯誤\n");
				}
			}
			else {
				printf("公式錯誤\n");
			}
		}
	}
	else {
		printf("公式錯誤\n");
	}

}
int Infix_prefix(char str[], char stack_1[]) {//中轉前
	char ans[20] = {};

	int cc[2] = {};
	int count_2 = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == '(') {
			cc[0]++;
		}
		else if (str[i] == ')') {
			cc[1]++;
		}
	}
	if (cc[0] == cc[1])
	{
		cc[0] = 1;
		for (int i = 0; i < strlen(str); i++)
		{
			if (str[i] >= 65 && str[i] <= 90) {
				if (cc[0] == 1) {
					cc[0] = 0;
				}
				else {
					count_2 = 1;
					break;
				}
			}
			else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
				if (cc[0] == 0) {
					cc[0] = 1;
				}
				else {
					count_2 = 1;
					break;
				}
			}
		}
		if (count_2 == 1) {
			printf("公式錯誤\n");
			return 0;
		}
	}
	else {
		printf("公式錯誤\n");
		return 0;
	}


	int x = 0, y = 0;//x答案 y存的stack數量
	for (int i = strlen(str) - 1; i != -1; i--)
	{
		if (str[i] >= 65 && str[i] <= 90) {
			ans[x] = str[i];
			x++;
		}
		else if (str[i] == ')') {
			stack_1[y] = ')';
			y++;
		}
		else if (str[i] == '(') {
			for (int j = strlen(stack_1) - 1; j != -1; j--)
			{
				if (stack_1[j] != ')') {
					ans[x] = stack_1[j];
					stack_1[j] = '\0';
					y--;
					x++;
				}
				else {
					stack_1[j] = '\0';
					y--;
					break;
				}
			}
		}
		else if (str[i] == '*' || str[i] == '/') {
			stack_1[y] = str[i];
			y++;
			if (stack_1[y - 2] == '*' || stack_1[y - 2] == '/') {
				ans[x] = stack_1[y - 2];
				stack_1[y - 2] = stack_1[y - 1];
				stack_1[y - 1] = '\0';
				y--;
				x++;
			}
		}
		else if (str[i] == '+' || str[i] == '-') {
			stack_1[y] = str[i];
			y++;
			for (int j = y - 1; j != 0; j--)
			{
				if (stack_1[y - 2] == '+' || stack_1[y - 2] == '-' || stack_1[y - 2] == '*' || stack_1[y - 2] == '/') {
					ans[x] = stack_1[y - 2];
					stack_1[y - 2] = stack_1[y - 1];
					stack_1[y - 1] = '\0';
					y--;
					x++;
				}
			}
		}
	}
	for (int j = strlen(stack_1) - 1; j != -1; j--)
	{
		ans[x] = stack_1[j];
		x++;
	}
	strrev(ans);
	printf("%s\n", ans);
	return 0;
}
void postfix_Infix(char str[], char stack_1[]) {//後序轉中序
	char ans[10][20] = {};
	int top = 0;
	int count = 0;
	int counts = 0;
	int k = 0;

	int kk[2] = {};
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] >= 65 && str[i] <= 90) {
			kk[0]++;
		}
		else {
			kk[1]++;
		}
	}
	if (kk[0] - 1 == kk[1]) {//防一下
		for (int i = 0; i < strlen(str); i++)
		{
			if (str[i] >= 65 && str[i] <= 90) {
				ans[top][0] = str[i];

				top++;
				printf("stack: ");
				for (int j = 0; j < top; j++)
				{
					printf("%s", ans[j]);
				}
				printf("\n");
				counts++;
			}
			else if ((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') && counts > 0) {
				char string[10][10] = {};
				string[0][0] = str[i];
				strcat(ans[top - 2], string[0]);

				printf("\n");
				printf("add:%s\n", string[0]);

				printf("stack: ");
				for (int j = 0; j < top; j++)
				{
					printf("%s", ans[j]);
				}
				printf("\n");

				printf("\n");
				strcat(ans[top - 2], ans[top - 1]);
				memset(ans[top - 1], 0, 100);

				strcat(ans[top - 2], ")");
				for (int j = strlen(ans[top - 2]); j != 0; j--)
				{
					ans[top - 2][j] = ans[top - 2][j - 1];
				}
				ans[top - 2][0] = '(';
				printf("stack: ");
				for (int j = 0; j < top; j++)
				{
					printf("%s", ans[j]);
				}
				printf("\n");
				top--;
				counts--;
				count++;
			}
			else {
				printf("公式錯誤\n");
				k++;
				break;
			}
		}

		if (k == 0) {
			int cc[2] = {};
			int count_2 = 0;
			if (count != 0)
			{
				for (int i = 0; i < strlen(ans[0]); i++)
				{
					if (ans[0][i] == '(') {
						cc[0]++;
					}
					else if (ans[0][i] == ')') {
						cc[1]++;
					}
				}
				if (cc[0] == cc[1] && count * 2 == cc[0] + cc[1])
				{
					cc[0] = 1;
					for (int i = 0; i < strlen(ans[0]); i++)
					{
						if (ans[0][i] >= 65 && ans[0][i] <= 90) {
							if (cc[0] == 1) {
								cc[0] = 0;
							}
							else {
								count_2 = 1;
								break;
							}
						}
						else if (ans[0][i] == '+' || ans[0][i] == '-' || ans[0][i] == '*' || ans[0][i] == '/') {
							if (cc[0] == 0) {
								cc[0] = 1;
							}
							else {
								count_2 = 1;
								break;
							}
						}
					}
					if (count_2 == 0) {
						printf("%s\n", ans[0]);
					}
					else {
						printf("公式錯誤\n");
					}
				}
				else {
					printf("公式錯誤\n");

				}
			}
			else {
				printf("公式錯誤\n");
			}
		}
	}
	else {
		printf("輸入錯誤\n");
	}


}
int Infix_postfix(char str[], char stack_1[]) {//中轉後
	char ans[20] = {};
	int x = 0, y = 0;//x答案 y存的stack數量

	int cc[2] = {};
	int count_2 = 0;
	for (int i = 0; i < strlen(str); i++)//開防
	{
		if (str[i] == '(') {
			cc[0]++;
		}
		else if (str[i] == ')') {
			cc[1]++;
		}
	}
	if (cc[0] == cc[1])
	{
		cc[0] = 1;
		for (int i = 0; i < strlen(str); i++)
		{
			if (str[i] >= 65 && str[i] <= 90) {
				if (cc[0] == 1) {
					cc[0] = 0;
				}
				else {
					count_2 = 1;
					break;
				}
			}
			else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
				if (cc[0] == 0) {
					cc[0] = 1;
				}
				else {
					count_2 = 1;
					break;
				}
			}
		}
		if (count_2 == 1) {
			printf("公式錯誤\n");
			return 0;
		}
	}
	else {
		printf("公式錯誤\n");
		return 0;
	}
	//防完
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] >= 65 && str[i] <= 90) {
			ans[x] = str[i];
			printf("output:%s\tstack:%s\n", ans, stack_1);
			x++;
		}
		else if (str[i] == '(') {
			stack_1[y] = '(';
			printf("output:%s\tstack:%s\n", ans, stack_1);
			y++;
		}
		else if (str[i] == ')') {
			for (int j = strlen(stack_1) - 1; j != -1; j--)
			{
				if (stack_1[j] != '(') {
					ans[x] = stack_1[j];
					stack_1[j] = '\0';
					printf("output:%s\tstack:%s\n", ans, stack_1);
					y--;
					x++;
				}
				else {
					stack_1[j] = '\0';
					printf("output:%s\tstack:%s\n", ans, stack_1);
					y--;
					break;
				}
			}
		}
		else if (str[i] == '*' || str[i] == '/') {
			stack_1[y] = str[i];
			printf("output:%s\tstack:%s\n", ans, stack_1);
			y++;
			if (stack_1[y - 2] == '*' || stack_1[y - 2] == '/') {
				ans[x] = stack_1[y - 2];
				stack_1[y - 2] = stack_1[y - 1];
				stack_1[y - 1] = '\0';
				printf("output:%s\tstack:%s\n", ans, stack_1);
				y--;
				x++;
			}
		}
		else if (str[i] == '+' || str[i] == '-') {
			stack_1[y] = str[i];
			printf("output:%s\tstack:%s\n", ans, stack_1);
			y++;
			for (int j = y - 1; j != 0; j--)
			{
				if (stack_1[y - 2] == '+' || stack_1[y - 2] == '-' || stack_1[y - 2] == '*' || stack_1[y - 2] == '/') {
					ans[x] = stack_1[y - 2];
					stack_1[y - 2] = stack_1[y - 1];
					stack_1[y - 1] = '\0';
					printf("output:%s\tstack:%s\n", ans, stack_1);
					y--;
					x++;
				}
			}
		}
	}
	for (int j = strlen(stack_1) - 1; j != -1; j--)
	{
		ans[x] = stack_1[j];
		printf("output:%s\tstack:%s\n", ans, stack_1);
		x++;
	}
	printf("%s\n", ans);
	return 0;
}