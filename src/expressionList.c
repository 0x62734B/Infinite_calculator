#include "calculator.h"

// operCheck - �����ڿ� ���ڸ� ���� : 1 - ������, 0 - ���� 
// char - �������� ��� �����ڸ� ���� 

// ���ο� ������� ����Ʈ�� �� ��带 �������ִ� �޼��� 
expressionNode *newExpressionNode(int operCheck, NUM *n, char oper)
{
   expressionNode *temp = (expressionNode *)malloc(sizeof(expressionNode));
   if (operCheck) {
      temp->next = NULL;
      temp->num = NULL;
      temp->oper = oper;
   }
   else {
      temp->next = NULL;
      temp->num = n;
      temp->oper = 0;
   }
   return temp;
}

// ���� �����ϴ� ����Ʈ�� ���� ����� �޼���  
expressionList *newExpressionList(void)
{
   expressionList *temp = (expressionList *)malloc(sizeof(expressionList));
   temp->head = NULL;
   return temp;
}

// ����� ����Ʈ�� ���� ��带 �������ִ� �޼���  
expressionNode *getExpressionTail(expressionList *list)
{
   expressionNode *tail = list->head;
   while (1) {
      if (tail->next == NULL) break;
      tail = tail->next;
   }
   return tail;
}

// ���� ǥ����  ����Ʈ�� ��带 �߰������ִ� �޼��� 
void appendExpressionNode(expressionList *list, expressionNode *newnode)
{
   if (list->head == NULL) {
      list->head = newnode;
   }
   else {
      expressionNode *tail = getExpressionTail(list);
      tail->next = newnode;
   }
}

// ���� ǥ���� ����Ʈ�� ��� ��带 �����ϴ� �޼��� 
void deleteHeadExpressionNode(expressionList *list)
{
   if (list->head->next != NULL) {
      expressionNode *temp = list->head->next;
      free(list->head);
      list->head = temp;
   }
   else {
      free(list->head);
      list->head = NULL;
   }
}
