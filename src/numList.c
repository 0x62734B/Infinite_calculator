#include "calculator.h"

// ���ο� numNode�� num�� n���� next, prev�� NULL�� �ʱ�ȭ���ְ� �������ִ� �޼��� 
numNode *newNumNode(int n)
{
    numNode *temp = (numNode *)malloc(sizeof(numNode));
    temp->num = n;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

// ���ο� numLust�� �������ִ� �޼��� 
numList *newNumList(void)
{
    numList *temp = (numList *)malloc(sizeof(numList));
    temp->head = NULL;
    return temp;
}

// ���ο� ������ �����κа� �Ҽ��κ��� �����ϴ� ����Ʈ�� �ʱ�ȭ�� �������ִ� �޼��� 
NUM *newNUM(void)
{
    NUM *temp = (NUM *)malloc(sizeof(NUM));
    temp->integer = newNumList();
    temp->decimal = newNumList();
    temp->sign = 1;
    return temp;
}

// ���ο� numList�� �Է¹޾� �� ����Ʈ�� ���� ��带 �������ִ� �޼��� 
numNode *getNumNodeTail(numList *list)
{
    numNode *temp = list->head;
    while (1) {
       if (temp->next == NULL) break;
        temp = temp->next;
    }
    return temp;
}

// ����Ʈ�� ��带 �߰������ִ� �޼��� 
void appendNum(numList *list, numNode *newnode, int next)
{
    if (list->head == NULL) {
        list->head = newnode;
    }
    else {
        if (next) {
            numNode *tail = getNumNodeTail(list);
            tail->next = newnode;
            newnode->prev = tail;
        }
        else {
            newnode->next = list->head;
            list->head->prev = newnode;
            list->head = newnode;
        }
    }
}

// NUM�� ���ڷ� �޾� ����Ʈ���ִ� �޼��� 
void printNum(NUM *n)
{
    numNode *temp = n->integer->head;
    if (!n->sign) printf("-");
    while(temp != NULL) {
        printf("%d", temp->num);
        temp = temp->next;
    }
    if (n->decimal->head != NULL) {
        printf(".");
        temp = n->decimal->head;
        while(temp != NULL) {
            printf("%d", temp->num);
            temp = temp->next;
        }
    }
    printf("\n");
}
