#include "calculator.h"

// 숫사 연산자 공백을 제외한 문자를 입력하였을 경우 에러메시지를 띄우고 프로그램을 종료시키는 메서드  
void error_input(void)
{
    printf("ERROR: Invalid input.\n");
    exit(1);
}

// 식의 표현이 잘못되었을 경우에 에러메시지를 띄우고 프로그램을 종료시키는 메서드 
void error_expression(void)
{
    printf("ERROR: Invalid expression.\n");
	exit(1);
}

// 한 숫자내에서 소수점이 2개 이상이 나왔을 경우 에러메시지를 띄우고 프로그램을 종료시키는 메서드 
void error_point(void)
{
    printf("ERROR: There are more than one decimal point in one number.\n");
    exit(1);
}

// 괄호의 쌍이 일치하지 않았을 경우 에러메시지를 띄우고 프로그램을 종료시키는 메서드 
void error_parenthesis(void)
{
    printf("ERROR: Parentheses do not match.\n");
    exit(1);
}
