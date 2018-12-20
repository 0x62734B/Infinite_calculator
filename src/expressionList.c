#include "calculator.h"

// operCheck - 연산자와 숫자를 구분 : 1 - 연산자, 0 - 숫자 
// char - 연산자일 경우 연산자를 저장 

// 새로운 식저장용 리스트에 들어갈 노드를 리턴해주는 메서드 
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

// 식을 저장하는 리스트를 새로 만드는 메서드  
expressionList *newExpressionList(void)
{
   expressionList *temp = (expressionList *)malloc(sizeof(expressionList));
   temp->head = NULL;
   return temp;
}

// 저장된 리스트의 꼬리 노드를 리턴해주는 메서드  
expressionNode *getExpressionTail(expressionList *list)
{
   expressionNode *tail = list->head;
   while (1) {
      if (tail->next == NULL) break;
      tail = tail->next;
   }
   return tail;
}

// 식을 표현한  리스트에 노드를 추가시켜주는 메서드 
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

// 식을 표현한 리스트의 헤드 노드를 삭제하는 메서드 
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
