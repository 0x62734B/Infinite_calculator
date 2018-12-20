#include "calculator.h"
#include <time.h>

long long getElapsedTime(unsigned int nFlag)
{
    const long long NANOS = 1000000000LL;
    static struct timespec startTS, endTS;
    static long long retDiff = 0;
    
    if (nFlag == 0) {
        retDiff = 0;
        if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTS) == -1) {
            printf("Failed to call clock_gettime\n");
        }
    }
    else {
        if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endTS) == -1) {
            printf("Failed to call clock_gettime\n");
        }
        retDiff = NANOS * (endTS.tv_sec - startTS.tv_sec) + (endTS.tv_nsec - startTS.tv_nsec);
    }
    
    return retDiff;
}

// ���� �Լ� 
int main() {
    getElapsedTime(0);
    
   expressionList *infix = newExpressionList();	//infix���� �޴� ����Ʈ ���� 
   input(infix);
   
   // ���� ������� ��ġ�� 
   expressionNode *temp = infix->head;
   
   //infix -> postfix ��ȯ�� �� ���� 
   expressionList *postfix = newExpressionList();
   infixToPostfix(infix, postfix);
   free(infix);		// infix�� �� �̻� ���x 
   
   // postfix ������� ��ġ�� 
   temp = postfix->head;
   // postfix �� ��� 
   NUM *ans = calculate(postfix);
   cleansing(ans);
   printNum(ans);
    
    printf("Elapsed Time: %lld\n", getElapsedTime(1));
    
   return 0;
}
