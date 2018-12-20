#include "calculator.h"

// 연산자의 우선순위를 리턴 
int precedence(char c)
{
    if (c == '*') return 2;
    else if (c == '+' || c == '-') return 1;
    else return 0;
}

// infix로 표현된 식이 저장된 리스트를 postfix 로 표현하는 메서드 
void infixToPostfix(expressionList *infix, expressionList *postfix)
{
	// 연산자 저장 리스트 생성
   charStack *stack = newCharStack();
   
   while (1) {
   		//  infix head부터 검사 
   		//	head가 숫자일 때
      if (!infix->head->oper) {
         appendExpressionNode(postfix, newExpressionNode(0, infix->head->num, 0));
         deleteHeadExpressionNode(infix);
      }
      
      // head가 연산자일 때 
      else {
         char oper = infix->head->oper;
         deleteHeadExpressionNode(infix);
         if (oper == '(') {
            pushToCharStack(stack, newCharStackNode(oper));
         }
         else if (oper == ')') {
         	//	charstack에서 '('가 나올때까지 pop해서 postfix에 append 
            while (stack->top->oper != '(') {
            	// ')' 개수가 더 많을 때 에러 
                if (stack->top->prev == NULL) error_parenthesis();
               appendExpressionNode(postfix, newExpressionNode(1, NULL, popFromCharStack(stack)));
            }
            popFromCharStack(stack);
         }
         
         // charstack->top의 가중치 >= infix->head의 가중치 = charstack->top을 postfix에 append
		 // else = infix->head를 charstack에 push
		 // infix->head를 다음 node로 옮기기는 공통 
         else if (oper == '*' || oper == '+' || oper == '-') {
            int weight1 = precedence(oper), weight2;
            if (stack->top != NULL) weight2 = precedence(stack->top->oper);
            while (stack->top != NULL && weight2 >= weight1) {
               appendExpressionNode(postfix, newExpressionNode(1, NULL, popFromCharStack(stack)));
               if (stack->top != NULL) weight2 = precedence(stack->top->oper);
            }
            pushToCharStack(stack, newCharStackNode(oper));
         }
      }
      if (infix->head == NULL) break;
   }
   
   // 나머지 연산자를 postfix에 append 
   while (stack->top != NULL) {
   		// '(' 개수가 더 많을 때 에러 
       if (stack->top->oper == '(') {
           error_parenthesis();
       }
      appendExpressionNode(postfix, newExpressionNode(1, NULL, popFromCharStack(stack)));
   }
}
