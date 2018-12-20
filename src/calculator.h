#include <stdio.h>
#include <stdlib.h>

/*
    숫자 저장용 리스트
 
    구조체
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
   식 저장용 리스트 
*/

typedef struct expressionNode {
   NUM *num;                        // NULL이면 연산자 있고 아니면 연산자 있음.
   char oper;                       // 0이면 연산자 없고 0이 아닌 값이면 + - * 중 하나. 
   struct expressionNode *next;
} expressionNode;

typedef struct {
   expressionNode *head;
} expressionList;

/*
   infix to postfix 연산자 스택 
*/

typedef struct charStackNode {
    char oper;
    struct charStackNode *prev;
} charStackNode;

typedef struct {
    charStackNode *top;
} charStack;

/*
   postfix를 계산할때 사용하는 숫자 리스트의 포인터 스택 
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
