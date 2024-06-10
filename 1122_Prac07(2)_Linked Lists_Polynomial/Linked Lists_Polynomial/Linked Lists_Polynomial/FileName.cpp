#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int coefficient;
    int power;
    struct node* next;
};

struct node* create_node(int coe, int power) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->coefficient = coe;
    new_node->power = power;
    new_node->next = NULL;
    return new_node;
}

void insert_term(struct node** head, int coe, int power) {
    struct node* new_node = create_node(coe, power);
    if (*head == NULL || (*head)->power < power) {
        new_node->next = *head;
        *head = new_node;
    }
    else {
        struct node* current = *head;
        while (current->next != NULL && current->next->power > power) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void print_polynomial(struct node* head) {
    struct node* current = head;
    int isFirstTerm = 1; // 标记是否为多项式的第一个项

    while (current != NULL) {
        // 如果不是第一个项，且系数为正，打印加号
        if (!isFirstTerm && current->coefficient > 0) {
            printf(" +");
        }


        printf(" %d", current->coefficient);

        // 处理变量X和幂次
        if (current->power > 0) {
            printf("X");
            if (current->power > 1) {
                printf("^%d", current->power);
            }
        }

        isFirstTerm = 0; // 更新标记，表示已处理过第一个项
        current = current->next;
    }
    printf("\n");
}


struct node* add_polynomials(struct node* head1, struct node* head2);
struct node* multiply_polynomials(struct node* poly1, struct node* poly2);

int get_length(struct node* head) {
    int length = 0;
    struct node* current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

struct node* invert_polynomial(struct node* head) {
    struct node* prev = NULL;
    struct node* current = head;
    struct node* next = NULL;

    while (current != NULL) {
        next = current->next;  // 保存下一个节点
        current->next = prev;  // 反转当前节点的指针
        prev = current;        // 步进：prev和current都前进一位
        current = next;
    }

    return prev; // prev变成了新的头节点
}

int main() {
    struct node* head_A = NULL;
    struct node* head_B = NULL;
    FILE* fp;
    fp = fopen("輸入範例.txt", "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    char line[1024];
    int line_number = 0;
    while (fgets(line, sizeof(line), fp)) {
        char* token = strtok(line, " \n");
        char sign = '+';
        while (token != NULL) {
            int coe, pow = 0;
            if (token[0] == '-') {
                sign = '-';
            }
            if (token[0] == '+') {
                sign = '+';
            }
            if (sscanf(token, "%dx^%d", &coe, &pow) == 2) {
                if (sign == '-') {
                    coe = -coe; // 将系数变为负数
                }
                if (line_number == 0) {
                    insert_term(&head_A, coe, pow);
                }
                else {
                    insert_term(&head_B, coe, pow);
                }
            }
            else if (sscanf(token, "%d", &coe) == 1) { // 解析常数项，包括负数
                if (sign == '-') {
                    coe = -coe; // 将系数变为负数
                }
                if (line_number == 0) {
                    insert_term(&head_A, coe, 0);
                }
                else {
                    insert_term(&head_B, coe, 0);
                }
            }
            token = strtok(NULL, " \n");
        }
        line_number++;
    }

    fclose(fp);

    printf("Polynomial A: ");
    print_polynomial(head_A);
    printf("Polynomial B: ");
    print_polynomial(head_B);

    int choice = 0;
    while (true) {
        printf("\n請輸入選項 1)a+b\t2)a*b\t3)a+b長度跟a*b長度\t4)a+b長度跟a*b的invert\t-1)結束 :");
        scanf("%d", &choice);
        if (choice == -1) {
            break;
        }
        else if (choice == 1) {
            struct node* head_sum = add_polynomials(head_A, head_B);
            printf("a跟b相加\t: ");
            print_polynomial(head_sum);
        }
        else if (choice == 2) {
            struct node* product = multiply_polynomials(head_A, head_B);
            printf("a跟b相乘\t: ");
            print_polynomial(product);
        }
        else if (choice == 3) {
            struct node* result_1;
            struct node* result_2;
            result_1 = add_polynomials(head_A, head_B);
            result_2 = multiply_polynomials(head_A, head_B);
            printf("a+b Length\t: %d\n", get_length(result_1));
            printf("a*b Length\t: %d\n", get_length(result_2));
        }
        else if (choice == 4) {
            struct node* result_1;
            struct node* result_2;
            result_1 = add_polynomials(head_A, head_B);
            result_2 = multiply_polynomials(head_A, head_B);
            struct node* invert_result_1;
            struct node* invert_result_2;

            printf("a+b Invert\t:");
            invert_result_1 = invert_polynomial(result_1);
            print_polynomial(invert_result_1);
            printf("a*b Invert\t:");
            invert_result_2 = invert_polynomial(result_2);
            print_polynomial(invert_result_2);
        }
    }
    // 释放链表内存
    struct node* tmp;
    while (head_A != NULL) {
        tmp = head_A;
        head_A = head_A->next;
        free(tmp);
    }
    while (head_B != NULL) {
        tmp = head_B;
        head_B = head_B->next;
        free(tmp);
    }
    return 0;
}


struct node* add_polynomials(struct node* head1, struct node* head2) {
    struct node* ptr1 = head1;
    struct node* ptr2 = head2;
    struct node* head_sum = NULL;

    // 循环遍历两个多项式链表并将它们相加
    while (ptr1 != NULL && ptr2 != NULL) {
        if (ptr1->power > ptr2->power) {
            insert_term(&head_sum, ptr1->coefficient, ptr1->power);
            ptr1 = ptr1->next;
        }
        else if (ptr1->power < ptr2->power) {
            insert_term(&head_sum, ptr2->coefficient, ptr2->power);
            ptr2 = ptr2->next;
        }
        else {
            int sum_coe = ptr1->coefficient + ptr2->coefficient;
            if (sum_coe != 0) { // 如果系数和不为0，则插入新项
                insert_term(&head_sum, sum_coe, ptr1->power);
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }

    // 复制剩余项
    while (ptr1 != NULL) {
        insert_term(&head_sum, ptr1->coefficient, ptr1->power);
        ptr1 = ptr1->next;
    }
    while (ptr2 != NULL) {
        insert_term(&head_sum, ptr2->coefficient, ptr2->power);
        ptr2 = ptr2->next;
    }

    return head_sum;
}

struct node* multiply_polynomials(struct node* poly1, struct node* poly2) {
    struct node* result = NULL;
    struct node* p1 = poly1;
    struct node* p2 = poly2;
    struct node* temp = NULL;

    while (p1 != NULL) {
        while (p2 != NULL) {
            int coe = p1->coefficient * p2->coefficient;
            int pow = p1->power + p2->power;

            // 临时链表用于存储单项乘法结果
            insert_term(&temp, coe, pow);

            p2 = p2->next;
        }
        // 将临时链表的结果加到最终结果链表中
        result = add_polynomials(result, temp);

        // 清除临时链表以供下次使用
        struct node* clear;
        while (temp != NULL) {
            clear = temp;
            temp = temp->next;
            free(clear);
        }
        p1 = p1->next;
    }

    return result;
}