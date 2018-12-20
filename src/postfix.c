#include "calculator.h"

// �������� �켱������ ���� 
int precedence(char c)
{
    if (c == '*') return 2;
    else if (c == '+' || c == '-') return 1;
    else return 0;
}

// infix�� ǥ���� ���� ����� ����Ʈ�� postfix �� ǥ���ϴ� �޼��� 
void infixToPostfix(expressionList *infix, expressionList *postfix)
{
	// ������ ���� ����Ʈ ����
   charStack *stack = newCharStack();
   
   while (1) {
   		//  infix head���� �˻� 
   		//	head�� ������ ��
      if (!infix->head->oper) {
         appendExpressionNode(postfix, newExpressionNode(0, infix->head->num, 0));
         deleteHeadExpressionNode(infix);
      }
      
      // head�� �������� �� 
      else {
         char oper = infix->head->oper;
         deleteHeadExpressionNode(infix);
         if (oper == '(') {
            pushToCharStack(stack, newCharStackNode(oper));
         }
         else if (oper == ')') {
         	//	charstack���� '('�� ���ö����� pop�ؼ� postfix�� append 
            while (stack->top->oper != '(') {
            	// ')' ������ �� ���� �� ���� 
                if (stack->top->prev == NULL) error_parenthesis();
               appendExpressionNode(postfix, newExpressionNode(1, NULL, popFromCharStack(stack)));
            }
            popFromCharStack(stack);
         }
         
         // charstack->top�� ����ġ >= infix->head�� ����ġ = charstack->top�� postfix�� append
		 // else = infix->head�� charstack�� push
		 // infix->head�� ���� node�� �ű��� ���� 
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
   
   // ������ �����ڸ� postfix�� append 
   while (stack->top != NULL) {
   		// '(' ������ �� ���� �� ���� 
       if (stack->top->oper == '(') {
           error_parenthesis();
       }
      appendExpressionNode(postfix, newExpressionNode(1, NULL, popFromCharStack(stack)));
   }
}
