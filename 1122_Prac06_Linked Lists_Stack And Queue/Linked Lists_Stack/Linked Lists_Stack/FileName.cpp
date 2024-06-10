#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 5

typedef struct Node {
    char data[100];
    struct Node* next;
} Node;

void push(Node** top, char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data, value);
    newNode->next = *top;
    *top = newNode;
}

// 修改pop函數的原型，加入一個用於接收彈出值的參數
void pop(Node** top, char* outValue) {
    if (*top == NULL) {
        strcpy(outValue, ""); // 如果堆疊空，則返回空字符串
        return;
    }
    Node* temp = *top;
    strcpy(outValue, temp->data); // 將資料複製到outValue
    *top = (*top)->next;
    free(temp);
}

int size(Node* top) {
    int count = 0;
    while (top != NULL) {
        count++;
        top = top->next;
    }
    return count;
}

int main() {
    Node* top = NULL;
    int choice;
    char input[100] = {};
    char poppedValue[100] = {}; // 定義一個變量用於接收彈出的值

    while (1) {
        printf("輸入1進行PUSH操作，輸入2進行POP操作，輸入-1結束程式：");
        scanf("%d", &choice);

        if (choice == -1) {
            break;
        }

        switch (choice) {
        case 1:
            if (size(top) >= MAX_SIZE) {
                printf("堆疊已滿，無法添加更多元素。\n");
            }
            else {
                printf("輸入字符串：");
                scanf("%s", input);
                push(&top, input);
                printf("現在Stack大小(%d/5)\n\n", size(top));
            }
            break;
        case 2:
            if (top == NULL) {
                printf("堆疊是空的。\n");
            }
            else {
                pop(&top, poppedValue); // 使用poppedValue接收彈出的值
                printf("移出的元素是：%s\n", poppedValue);
                printf("現在Stack大小(%d/5)\n\n", size(top));
            }
            break;
        default:
            printf("無效的輸入。\n");
            break;
        }
    }

    // 程式結束前釋放所有節點
    while (top != NULL) {
        pop(&top, poppedValue); // 這裡的poppedValue可以是任何緩衝區，因為這裡不關心彈出的值
    }

    return 0;
}
