#include "calculator.h"

charStackNode *newCharStackNode(char c)
{
    charStackNode *temp = (charStackNode *)malloc(sizeof(charStackNode));
    temp->oper = c;
    temp->prev = NULL;
    return temp;
}

charStack *newCharStack(void)
{
    charStack *temp = (charStack *)malloc(sizeof(charStack));
    temp->top = NULL;
    return temp;
}

void pushToCharStack(charStack *stack, charStackNode *newnode)
{
    newnode->prev = stack->top;
    stack->top = newnode;
}

char popFromCharStack(charStack *stack)
{
    char poped = stack->top->oper;
    charStackNode *temp = stack->top->prev;
    free(stack->top);
    stack->top = temp;
    return poped;
}

numStackNode *newNumStackNode(NUM *n)
{
    numStackNode *temp = (numStackNode *)malloc(sizeof(numStackNode));
    temp ->num = n;
    temp->prev = NULL;
    return temp;
}

numStack *newNumStack(void)
{
    numStack *temp = (numStack *)malloc(sizeof(numStack));
    temp->top = NULL;
    return temp;
}

void pushToNumStack(numStack *stack, numStackNode *newnode)
{
    newnode->prev = stack->top;
    stack->top = newnode;
}

NUM *popFromNumStack(numStack *stack)
{
    NUM *poped = stack->top->num;
    numStackNode *temp = stack->top->prev;
    free(stack->top);
    stack->top = temp;
    return poped;
}
