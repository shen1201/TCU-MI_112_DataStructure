#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Node {
	int data;
	Node* left;
	Node* right;
};
Node* creat_Node(int data);
void insert_Node(Node** root, int data);
void Inorder(Node* root);
void Preorder(Node* root);
void Postorder(Node* root);
void search_tree_node(Node* root, int data);
int main() {
	FILE* fp;
	fp = fopen("111.txt", "r");
	if (!fp) {
		perror("檔案開啟失敗"); // 將訊息輸出至 stderr
		return EXIT_FAILURE;
	}
	int number[100] = {};
	int count = 0;
	Node* root = NULL;

	while (!feof(fp)) {
		fscanf(fp, "%d", &number[count]);
		count++;
	}



	printf("Insert nodes: ");
	for (int i = 0; i < count; i++)
	{
		printf("%d ", number[i]);
		insert_Node(&root, number[i]);
	}
	printf("\n");
	printf("\nInorder:");
	Inorder(root);
	printf("\nPreorder:");
	Preorder(root);
	printf("\nPostorder:");
	Postorder(root);
	printf("\n");
	printf("\n");
	int choose = 0, num;
	while (choose != -1) {
		printf("(1)Search (-1)Exit:");
		scanf("%d", &choose);
		if (choose == 1) {
			printf("請輸入要搜尋的數:");
			scanf("%d", &num);
			search_tree_node(root, num);
		}
		else if (choose == -1) {
			break;
		}
		else {
			printf("輸入錯誤\n");
		}
	}


	fclose(fp);
	return 0;
}
Node* creat_Node(int data) {
	Node* root = (Node*)malloc(sizeof(Node));
	root->data = data;
	root->left = NULL;
	root->right = NULL;
	return root;
}
void insert_Node(Node** root, int data) {
	if (*root == NULL) {
		*root = creat_Node(data);
	}
	else if ((*root)->data >= data) {
		insert_Node(&(*root)->left, data);
	}
	else if ((*root)->data < data) {
		insert_Node(&(*root)->right, data);
	}
}
void Inorder(Node* root) {
	if (root != NULL) {
		Inorder(root->left);
		printf("%d ", root->data);
		Inorder(root->right);
	}
}
void Preorder(Node* root) {
	if (root != NULL) {
		printf("%d ", root->data);
		Preorder(root->left);
		Preorder(root->right);
	}
}
void Postorder(Node* root) {
	if (root != NULL) {
		Postorder(root->left);
		Postorder(root->right);
		printf("%d ", root->data);
	}
}
void search_tree_node(Node* root, int data) {
	if (root == NULL) {
		printf("Fail\n");
	}
	else if (root->data == data) {
		printf("Success\n");
	}
	else if (root->data >= data) {
		search_tree_node(root->left, data);
	}
	else if (root->data < data) {
		search_tree_node(root->right, data);
	}
}