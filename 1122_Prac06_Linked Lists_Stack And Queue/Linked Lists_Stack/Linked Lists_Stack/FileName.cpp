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

// �ק�pop��ƪ��쫬�A�[�J�@�ӥΩ󱵦��u�X�Ȫ��Ѽ�
void pop(Node** top, char* outValue) {
    if (*top == NULL) {
        strcpy(outValue, ""); // �p�G���|�šA�h��^�Ŧr�Ŧ�
        return;
    }
    Node* temp = *top;
    strcpy(outValue, temp->data); // �N��ƽƻs��outValue
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
    char poppedValue[100] = {}; // �w�q�@���ܶq�Ω󱵦��u�X����

    while (1) {
        printf("��J1�i��PUSH�ާ@�A��J2�i��POP�ާ@�A��J-1�����{���G");
        scanf("%d", &choice);

        if (choice == -1) {
            break;
        }

        switch (choice) {
        case 1:
            if (size(top) >= MAX_SIZE) {
                printf("���|�w���A�L�k�K�[��h�����C\n");
            }
            else {
                printf("��J�r�Ŧ�G");
                scanf("%s", input);
                push(&top, input);
                printf("�{�bStack�j�p(%d/5)\n\n", size(top));
            }
            break;
        case 2:
            if (top == NULL) {
                printf("���|�O�Ū��C\n");
            }
            else {
                pop(&top, poppedValue); // �ϥ�poppedValue�����u�X����
                printf("���X�������O�G%s\n", poppedValue);
                printf("�{�bStack�j�p(%d/5)\n\n", size(top));
            }
            break;
        default:
            printf("�L�Ī���J�C\n");
            break;
        }
    }

    // �{�������e����Ҧ��`�I
    while (top != NULL) {
        pop(&top, poppedValue); // �o�̪�poppedValue�i�H�O����w�İϡA�]���o�̤����߼u�X����
    }

    return 0;
}
