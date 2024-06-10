#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node
{
	char data;
	struct Node* left;
	struct Node* right;
};

struct Node* creat(char data) {
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	if (node == NULL) {
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

int search(char* IN, char index, int len) {
	for (int i = 0; i < len; i++)
	{
		if (IN[i] == index) {
			return i;
		}
	}
	return -1;
}

struct Node* function(char* IN, char* PRE, int start, int end, int* len) {
	if (start > end) {
		return NULL;
	}

	char index = PRE[*len];
	(*len)++;
	struct Node* root = creat(index);
	if (start == end) {
		return root;
	}

	int inorder_index = search(IN, index, end + 1);
	root->left = function(IN, PRE, start, inorder_index - 1, len);
	root->right = function(IN, PRE, inorder_index + 1, end, len);

	return root;
}

void post(struct Node* root) {
	if (root == NULL)
		return;
	post(root->left);
	post(root->right);
	printf("%c", root->data);
}
int main() {
	FILE* fp;
	fp = fopen("前中01.txt", "r");

	if (!fp) {
		printf("找不到此檔案\n");
		return -1;
	}
	char IN[100] = {};
	char PRE[100] = {};
	int count = 0;
	char eat;
	int tag = 0;
	fscanf(fp, "%c", &eat);
	while (!feof(fp)) {
		if (eat == '\n') {
			tag++;
			count = 0;
		}
		else if (eat != ' ' && tag == 0) {
			PRE[count] = eat;
			count++;
		}
		else if (eat != ' ' && tag == 1) {
			IN[count] = eat;
			count++;
		}
		fscanf(fp, "%c", &eat);

	}
	printf("%s\n", PRE);
	printf("%s\n", IN);
	int n = 0;
	Node* tree = function(IN, PRE, 0, count - 1, &n);
	post(tree);
	return 0;
}