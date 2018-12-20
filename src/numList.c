#include "calculator.h"

// 새로운 numNode의 num은 n으로 next, prev는 NULL로 초기화해주고 리턴해주는 메서드 
numNode *newNumNode(int n)
{
    numNode *temp = (numNode *)malloc(sizeof(numNode));
    temp->num = n;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

// 새로운 numLust를 리턴해주는 메서드 
numList *newNumList(void)
{
    numList *temp = (numList *)malloc(sizeof(numList));
    temp->head = NULL;
    return temp;
}

// 새로운 숫자의 정수부분과 소수부분을 저장하는 리스트를 초기화후 리터해주는 메서드 
NUM *newNUM(void)
{
    NUM *temp = (NUM *)malloc(sizeof(NUM));
    temp->integer = newNumList();
    temp->decimal = newNumList();
    temp->sign = 1;
    return temp;
}

// 새로운 numList를 입력받아 그 리스트에 꼬리 노드를 리턴해주는 메서드 
numNode *getNumNodeTail(numList *list)
{
    numNode *temp = list->head;
    while (1) {
       if (temp->next == NULL) break;
        temp = temp->next;
    }
    return temp;
}

// 리스트에 노드를 추가시켜주는 메서드 
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

// NUM을 인자로 받아 프린트해주는 메서드 
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
