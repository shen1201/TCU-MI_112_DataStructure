#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int num;
    struct Node* ptr;
};
typedef struct Node Node;
typedef struct Node* NodePtr;

void InsertNode(Node** head, int input);
void Add(Node** headA, Node** headB);
void Delete(Node** headA, Node** headB);
void show(Node* head);
int CountNodes(Node* head);

int main()
{
    NodePtr headA = NULL;
    NodePtr headB = NULL;
    int choice, input;

    printf("1)��A list 2)��B list 3)��B���A 4)��A������B�R�� -1)���}\n");
    scanf("%d", &choice);
    while (choice != -1)
    {
        switch (choice)
        {
        case 1:
            printf("insert to A�G");
            scanf("%d", &input);
            InsertNode(&headA, input);

            printf("list A��%d�ӭȡG", CountNodes(headA));
            show(headA);

            printf("\nlist B��%d�ӭȡG", CountNodes(headB));
            show(headB);
            break;

        case 2:
            printf("insert to B�G");
            scanf("%d", &input);
            InsertNode(&headB, input);

            printf("list A��%d�ӭȡG", CountNodes(headA));
            show(headA);

            printf("\nlist B��%d�ӭȡG", CountNodes(headB));
            show(headB);
            break;

        case 3:
            Add(&headA, &headB);

            printf("list A��%d�ӭȡG", CountNodes(headA));
            show(headA);

            printf("\nlist B��%d�ӭȡG", CountNodes(headB));
            show(headB);

            headB = NULL; //�Ҧ�B���`�I�w�Q�[�J��A��
            break;

        case 4:
            Delete(&headA, &headB);

            printf("list A��%d�ӭȡG", CountNodes(headA));
            show(headA);

            printf("\nlist B��%d�ӭȡG", CountNodes(headB));
            show(headB);

            headB = NULL;  //A���PB�ۦP�Ȫ��`�I�w�Q�R��
            break;

        case -1:
            printf("����\n");
            break;

        default:
            printf("error\n");
        }
        printf("\n\n(1)��A (2)��B (3)��B���A (4)��A����B���R�� (-1)���}�G");
        scanf("%d", &choice);
    }
    return 0;
}


//�����Ǵ��J�s�`�I
void InsertNode(Node** head, int input)
{
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->num = input;
    newNode->ptr = NULL;

    if (*head == NULL || input > (*head)->num) //���J�Y��
    {
        newNode->ptr = *head;
        *head = newNode;
    }
    else { //���J����
        Node* curPtr = *head;

        while (curPtr->ptr != NULL && curPtr->ptr->num > input)
        {
            curPtr = curPtr->ptr;
        }
        newNode->ptr = curPtr->ptr;
        curPtr->ptr = newNode;
    }
}

void Add(Node** headA, Node** headB)
{
    Node* curPtrB = *headB;

    while (curPtrB != NULL)
    {
        InsertNode(headA, curPtrB->num);

        Node* temp = curPtrB;

        curPtrB = curPtrB->ptr;
        free(temp);
    }

    *headB = NULL;
}

void Delete(Node** headA, Node** headB)
{
    if (*headA == NULL || *headB == NULL)
    {
        return;
    }

    Node* curPtrA = *headA;
    Node* curPtrB = *headB;

    while (curPtrB != NULL)
    {
        Node* prePtrA = NULL;
        curPtrA = *headA;
        while (curPtrA != NULL)
        {
            if (curPtrA->num == curPtrB->num)
            {
                Node* temp = curPtrA;

                if (prePtrA == NULL) //�R�����O�Y
                {
                    *headA = curPtrA->ptr;
                    free(temp);
                    curPtrA = *headA;
                }
                else //�R�����O����
                {
                    prePtrA->ptr = curPtrA->ptr;
                    free(temp);
                    curPtrA = prePtrA->ptr;
                }
            }
            else
            {
                prePtrA = curPtrA;
                curPtrA = curPtrA->ptr;
            }
        }

        curPtrB = curPtrB->ptr;
    }

    *headB = NULL;
}

void show(Node* head)
{
    Node* curPtr = head;

    while (curPtr != NULL)
    {
        printf("%d", curPtr->num);

        if (curPtr->ptr != NULL)
        {
            printf("->");
        }
        curPtr = curPtr->ptr;
    }
}

//�p��`�I�ƶq
int CountNodes(Node* head)
{
    int count = 0;
    Node* curPtr = head;

    while (curPtr != NULL)
    {
        count++;
        curPtr = curPtr->ptr;
    }
    return count;
}