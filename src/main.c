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

// 메인 함수 
int main() {
    getElapsedTime(0);
    
   expressionList *infix = newExpressionList();	//infix식을 받는 리스트 생성 
   input(infix);
   
   // 식의 구성요소 펼치기 
   expressionNode *temp = infix->head;
   
   //infix -> postfix 변환한 식 저장 
   expressionList *postfix = newExpressionList();
   infixToPostfix(infix, postfix);
   free(infix);		// infix는 더 이상 사용x 
   
   // postfix 순서대로 펼치기 
   temp = postfix->head;
   // postfix 식 계산 
   NUM *ans = calculate(postfix);
   cleansing(ans);
   printNum(ans);
    
    printf("Elapsed Time: %lld\n", getElapsedTime(1));
    
   return 0;
}
