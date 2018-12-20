#include "calculator.h"

// ���� ������ ������ ������ ���ڸ� �Է��Ͽ��� ��� �����޽����� ���� ���α׷��� �����Ű�� �޼���  
void error_input(void)
{
    printf("ERROR: Invalid input.\n");
    exit(1);
}

// ���� ǥ���� �߸��Ǿ��� ��쿡 �����޽����� ���� ���α׷��� �����Ű�� �޼��� 
void error_expression(void)
{
    printf("ERROR: Invalid expression.\n");
	exit(1);
}

// �� ���ڳ����� �Ҽ����� 2�� �̻��� ������ ��� �����޽����� ���� ���α׷��� �����Ű�� �޼��� 
void error_point(void)
{
    printf("ERROR: There are more than one decimal point in one number.\n");
    exit(1);
}

// ��ȣ�� ���� ��ġ���� �ʾ��� ��� �����޽����� ���� ���α׷��� �����Ű�� �޼��� 
void error_parenthesis(void)
{
    printf("ERROR: Parentheses do not match.\n");
    exit(1);
}
