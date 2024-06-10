#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 5

typedef struct Node {
    char data[100];
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
    int count;
} Queue;

void initializeQueue(Queue* q) {
    q->front = q->rear = NULL;
    q->count = 0;
}

int isFull(Queue* q) {
    return q->count == MAX_SIZE;
}

int isEmpty(Queue* q) {
    return q->count == 0;
}

void enqueue(Queue* q, char* value) {
    if (isFull(q)) {
        printf("隊列已滿，無法添加更多元素。\n");
        return;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data, value);
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    }
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
}

void dequeue(Queue* q, char* outValue) {
    if (isEmpty(q)) {
        printf("隊列是空的。\n");
        strcpy(outValue, ""); // 如果隊列空，則返回空字符串
        return;
    }
    Node* temp = q->front;
    strcpy(outValue, temp->data); // 將資料複製到outValue
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    q->count--;
}

int main() {
    Queue q;
    initializeQueue(&q);
    int choice;
    char input[100] = {};
    char dequeuedValue[100] = {};

    while (1) {
        printf("輸入1進行Insert操作，輸入2進行Delete操作，輸入-1結束程式：");
        scanf("%d", &choice);

        if (choice == -1) {
            break;
        }

        switch (choice) {
        case 1:
            if (isFull(&q)) {
                printf("隊列已滿，無法添加更多元素。\n");
            }
            else {
                printf("輸入字符串：");
                scanf("%s", input);
                enqueue(&q, input);
                printf("現在Queue大小(%d/5)\n\n", q.count);
            }
            break;
        case 2:
            dequeue(&q, dequeuedValue);
            if (dequeuedValue[0] != '\0') {
                printf("移出的元素是：%s\n", dequeuedValue);
                printf("現在Queue大小(%d/5)\n\n", q.count);
            }
            break;
        default:
            printf("無效的輸入。\n");
            break;
        }
    }

    // 清理隊列
    while (!isEmpty(&q)) {
        dequeue(&q, dequeuedValue);
    }

    return 0;
}
