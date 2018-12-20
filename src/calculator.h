#include <stdio.h>
#include <stdlib.h>

/*
    ���� ����� ����Ʈ
 
    ����ü
        numNode            24byte
        numList            8byte
        NUM                24byte
*/

typedef struct numNode {
    int num;
    struct numNode *prev;
    struct numNode *next;
} numNode;

typedef struct {
    int size;
    numNode *head;
} numList;

typedef struct {
    int sign;               // 1 : +, 0 : -.
    numList *integer;
    numList *decimal;
} NUM;

/*
   �� ����� ����Ʈ 
*/

typedef struct expressionNode {
   NUM *num;                        // NULL�̸� ������ �ְ� �ƴϸ� ������ ����.
   char oper;                       // 0�̸� ������ ���� 0�� �ƴ� ���̸� + - * �� �ϳ�. 
   struct expressionNode *next;
} expressionNode;

typedef struct {
   expressionNode *head;
} expressionList;

/*
   infix to postfix ������ ���� 
*/

typedef struct charStackNode {
    char oper;
    struct charStackNode *prev;
} charStackNode;

typedef struct {
    charStackNode *top;
} charStack;

/*
   postfix�� ����Ҷ� ����ϴ� ���� ����Ʈ�� ������ ���� 
*/

typedef struct numStackNode {
    NUM *num;
    struct numStackNode *prev;
} numStackNode;

typedef struct {
    numStackNode *top;
} numStack;

numNode *newNumNode(int n);   
numList *newNumList(void);
NUM *newNUM(void);
numNode *getNumNodeTail(numList *list);
void appendNum(numList *list, numNode *newnode, int next);
void printNum(NUM *n);

expressionNode *newExpressionNode(int operCheck, NUM *n, char oper);
expressionList *newExpressionList(void);
expressionNode *getExpressionTail(expressionList *list);
void appendExpressionNode(expressionList *list, expressionNode *newnode);
void deleteHeadExpressionNode(expressionList *list);

charStackNode *newCharStackNode(char c);
charStack *newCharStack(void);
void pushToCharStack(charStack *stack, charStackNode *newnode);
char popFromCharStack(charStack *stack);

numStackNode *newNumStackNode(NUM *n);
numStack *newNumStack(void);
void pushToNumStack(numStack *stack, numStackNode *newnode);
NUM *popFromNumStack(numStack *stack);

void input(expressionList *list);

int precedence(char c);
void infixToPostfix(expressionList *infix, expressionList *postfix);

NUM *add(NUM *n1, NUM *n2);
NUM *substract(NUM *n1, NUM *n2);
NUM *multiply(NUM *n1, NUM *n2);

NUM *calculate(expressionList *postfix);
void cleansing(NUM *toClean);

void error_expression(void);
void error_input(void);
void error_point(void);
void error_parenthesis(void);
