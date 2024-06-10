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

    printf("1)建A list 2)建B list 3)把B丟到A 4)把A中有的B刪掉 -1)離開\n");
    scanf("%d", &choice);
    while (choice != -1)
    {
        switch (choice)
        {
        case 1:
            printf("insert to A：");
            scanf("%d", &input);
            InsertNode(&headA, input);

            printf("list A有%d個值：", CountNodes(headA));
            show(headA);

            printf("\nlist B有%d個值：", CountNodes(headB));
            show(headB);
            break;

        case 2:
            printf("insert to B：");
            scanf("%d", &input);
            InsertNode(&headB, input);

            printf("list A有%d個值：", CountNodes(headA));
            show(headA);

            printf("\nlist B有%d個值：", CountNodes(headB));
            show(headB);
            break;

        case 3:
            Add(&headA, &headB);

            printf("list A有%d個值：", CountNodes(headA));
            show(headA);

            printf("\nlist B有%d個值：", CountNodes(headB));
            show(headB);

            headB = NULL; //所有B的節點已被加入到A中
            break;

        case 4:
            Delete(&headA, &headB);

            printf("list A有%d個值：", CountNodes(headA));
            show(headA);

            printf("\nlist B有%d個值：", CountNodes(headB));
            show(headB);

            headB = NULL;  //A中與B相同值的節點已被刪除
            break;

        case -1:
            printf("結束\n");
            break;

        default:
            printf("error\n");
        }
        printf("\n\n(1)建A (2)建B (3)把B丟到A (4)把A中有B的刪掉 (-1)離開：");
        scanf("%d", &choice);
    }
    return 0;
}


//按降序插入新節點
void InsertNode(Node** head, int input)
{
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->num = input;
    newNode->ptr = NULL;

    if (*head == NULL || input > (*head)->num) //插入頭部
    {
        newNode->ptr = *head;
        *head = newNode;
    }
    else { //插入中間
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

                if (prePtrA == NULL) //刪除的是頭
                {
                    *headA = curPtrA->ptr;
                    free(temp);
                    curPtrA = *headA;
                }
                else //刪除的是中間
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

//計算節點數量
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