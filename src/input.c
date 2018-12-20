#include "calculator.h"

// 식을 입력받아서 숫자와 연산자를 구분하여 리스트에 추가시켜주는 메서드 
void input(expressionList *list)
{
	// spotcheck - 1이면 '.'이 이전에 나온 상태, 0이면 아직 나오지 않은 상태 
	// isExOper - 1이면 연산자, 0이면 숫자 
	// checkOpen,checkclose - 
    int spotCheck = 0, isExOper = 1, checkOpen = 0, checkClose = 0;
    NUM *n = newNUM();
    char c;
    while(scanf("%c", &c)) {
        if (c == '\n') {
           if (!checkClose) appendExpressionNode(list, newExpressionNode(0, n, 0));
         break;
      }
       else if (c == '.') {
           if (spotCheck) error_point();
          spotCheck = 1;
      }
        else if (c >= 48 && c <= 57) {
            if (checkClose) appendExpressionNode(list, newExpressionNode(1, NULL, '*'));
            if (spotCheck) {
                appendNum(n->decimal, newNumNode(c - '0'), 1);
            }
            else {
                appendNum(n->integer, newNumNode(c - '0'), 1);
            }
            isExOper = 0;
            checkOpen = 0;
            checkClose = 0;
        }
        else if (c == '-') {
			if (isExOper && !checkClose) {
				if (!n->sign) error_expression();
				n->sign = 0;
			}
			else {
				if (isExOper) {
				appendExpressionNode(list, newExpressionNode(1, NULL, c));
				}
				else {
					appendExpressionNode(list, newExpressionNode(0, n, 0));
					appendExpressionNode(list, newExpressionNode(1, NULL, c));
					n = newNUM();
				}
				spotCheck = 0;
				isExOper = 1;
				checkOpen = 0;
				checkClose = 0;
			}
		}
		else if (c == '+') {
			if (isExOper && !checkClose) error_expression();
			if (checkClose) {
				appendExpressionNode(list, newExpressionNode(1, NULL, c));
			}
			else {
				appendExpressionNode(list, newExpressionNode(0, n, 0));
				appendExpressionNode(list, newExpressionNode(1, NULL, c));
				n = newNUM();
			}
			spotCheck = 0;
			isExOper = 1;
			checkOpen = 0;
			checkClose = 0;
		}
        else if (c == '*') {
            if (isExOper && !checkClose) error_expression();
            if (checkClose) {
                appendExpressionNode(list, newExpressionNode(1, NULL, c));
            }
            else {
                appendExpressionNode(list, newExpressionNode(0, n, 0));
                appendExpressionNode(list, newExpressionNode(1, NULL, c));
                n = newNUM();
            }
            spotCheck = 0;
            isExOper = 1;
            checkOpen = 0;
            checkClose = 0;
        }
		else if (c == ')') {
			if (isExOper && !checkClose) error_expression();
			if (checkClose) {
				appendExpressionNode(list, newExpressionNode(1, NULL, c));
			}
			else {
				appendExpressionNode(list, newExpressionNode(0, n, 0));
				appendExpressionNode(list, newExpressionNode(1, NULL, c));
				n = newNUM();
			}
			spotCheck = 0;
			isExOper = 1;
			checkOpen = 0;
			checkClose = 1;
		}
		else if (c == '(') {
            if (!isExOper) {
                appendExpressionNode(list, newExpressionNode(0, n, 0));
                appendExpressionNode(list, newExpressionNode(1, NULL, '*'));
                n = newNUM();
            }
            else if (isExOper && !n->sign) {
                appendNum(n->integer, newNumNode(1), 1);
                appendExpressionNode(list, newExpressionNode(0, n, 0));
                appendExpressionNode(list, newExpressionNode(1, NULL, '*'));
                n = newNUM();
            }
			appendExpressionNode(list, newExpressionNode(1, NULL, c));
			spotCheck = 0;
			isExOper = 1;
			checkOpen = 1;
			checkClose = 0;
		}
		else if (c != ' ') {
			error_input();
		}	
    }
}
