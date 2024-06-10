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
        printf("���C�w���A�L�k�K�[��h�����C\n");
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
        printf("���C�O�Ū��C\n");
        strcpy(outValue, ""); // �p�G���C�šA�h��^�Ŧr�Ŧ�
        return;
    }
    Node* temp = q->front;
    strcpy(outValue, temp->data); // �N��ƽƻs��outValue
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
        printf("��J1�i��Insert�ާ@�A��J2�i��Delete�ާ@�A��J-1�����{���G");
        scanf("%d", &choice);

        if (choice == -1) {
            break;
        }

        switch (choice) {
        case 1:
            if (isFull(&q)) {
                printf("���C�w���A�L�k�K�[��h�����C\n");
            }
            else {
                printf("��J�r�Ŧ�G");
                scanf("%s", input);
                enqueue(&q, input);
                printf("�{�bQueue�j�p(%d/5)\n\n", q.count);
            }
            break;
        case 2:
            dequeue(&q, dequeuedValue);
            if (dequeuedValue[0] != '\0') {
                printf("���X�������O�G%s\n", dequeuedValue);
                printf("�{�bQueue�j�p(%d/5)\n\n", q.count);
            }
            break;
        default:
            printf("�L�Ī���J�C\n");
            break;
        }
    }

    // �M�z���C
    while (!isEmpty(&q)) {
        dequeue(&q, dequeuedValue);
    }

    return 0;
}
