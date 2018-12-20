#include "calculator.h"

// NUM 두 개를 인자로 받아 두 수를 더한 값이 저장된 NUM을 리턴해주는 메서드 
NUM *add(NUM *n1, NUM *n2)
{
	//  ceiling - 연산 시 자리수가 넘어가면 다음 자리수에 더해줄 수 
	//	check - NUM의 정수,소수부분  길이 측정 
   int check = 0, ceiling = 0;
   numNode *now1 = n1->decimal->head;
   numNode *now2 = n2->decimal->head;
   NUM *ans = newNUM();
   ans->sign = n1->sign;
    
    numNode *freed1;
    numNode *freed2;
   
   if (n1->decimal->head || n2->decimal->head){   
      while (1) {
         if (now1 == NULL && now2 == NULL) break;
         else if (now1 == NULL) {
            check = 2;
            break;
         }
         else if (now2 == NULL) {
            check = 1;
            break;
         }
         appendNum(ans->decimal, newNumNode(now1->num + now2->num), 1);
          freed1 = now1;
          freed2 = now2;
         now1 = now1->next;
         now2 = now2->next;
          free(freed1);
          free(freed2);
      }
      
      // 나머지 자리수를 더해줌 
      if (check == 1) {
         while (1) {
            appendNum(ans->decimal, newNumNode(now1->num), 1);
             freed1 = now1;
            now1 = now1->next;
             free(freed1);
            if (now1 == NULL) break;
         }
      }
      else if (check == 2) {
         while (1) {
            appendNum(ans->decimal, newNumNode(now2->num), 1);
             freed2 = now2;
            now2 = now2->next;
             free(freed2);
            if (now2 == NULL) break;
         }
      }
      
      check = 0;
      
      // 소수 리스트의 Tail을 가르킴 
      numNode *temp = getNumNodeTail(ans->decimal);
      
      // NumNode 의 소수부분의  num이 모두 한 자리 자연수가 되도록 정리 
      while (1) {
         int n = temp->num + ceiling;
         temp->num =  n % 10;
         ceiling = n / 10;
         temp = temp->prev;
         if (temp == NULL) break;
      }
   }
   
    //	정수 처리 준비 (1의 자리부터 덧셈 시작) 
   now1 = getNumNodeTail(n1->integer);
   now2 = getNumNodeTail(n2->integer);
   
   while (1) {      
      if (now1 == NULL && now2 == NULL) break;
      else if (now1 == NULL) {
         check = 2;
         break;
      }
      else if (now2 == NULL) {
         check = 1;
         break;
      }
      int n = now1->num + now2->num + ceiling;
      appendNum(ans->integer, newNumNode(n % 10), 0);
      ceiling = n / 10;
       freed1 = now1;
       freed2 = now2;
      now1 = now1->prev;
      now2 = now2->prev;
       free(freed1);
       free(freed2);
   }
   
   if (check == 1) {
      while (1) {
         int n = now1->num + ceiling;
         appendNum(ans->integer, newNumNode(n % 10), 0);
         ceiling = n / 10;
          freed1 = now1;
         now1 = now1->prev;
          free(freed1);
         if (now1 == NULL) break;
      }
   }
   else if (check == 2) {
      while (1) {
         int n = now2->num + ceiling;
         appendNum(ans->integer, newNumNode(n % 10), 0);
         ceiling = n / 10;
          freed2 = now2;
         now2 = now2->prev;
          free(freed2);
         if (now2 == NULL) break;
      }
   }
   
   //	넘기는 수가 연산하는 수보다 자리수가 크면 앞에다 ceiling을 append
   if (ceiling) appendNum(ans->integer, newNumNode(ceiling), 0);
   
   return ans;
}

// NUM 두 개를 인자로 받아 두 수를 뺀 값이 저장된 NUM을 리턴해주는 메서드
NUM *substract(NUM *n1, NUM *n2) 
{
	
	// chopping - ceiling과 같은 역할 
	// signchange - num의 부호 정리 
    int check = 0, chopping = 0, signChange = 0;
    NUM *ans = newNUM();
    
    //소수점 빼기 
    numNode *now1 = n1->decimal->head;
    numNode *now2 = n2->decimal->head;
    
    numNode *freed1;
    numNode *freed2;
    
    if(n1->decimal->head || n2->decimal->head) {
       while (1) {
           if (now1 == NULL && now2 == NULL) break;
           else if (now1 == NULL) {
               check = 2;
               break;
           }
           else if (now2 == NULL) {
               check = 1;
               break;
           }
           
           appendNum(ans->decimal, newNumNode(now1->num - now2->num), 1);
           freed1 = now1;
           freed2 = now2;
           now1 = now1->next;
           now2 = now2->next;
           free(freed1);
           free(freed2);
       }
       
       if (check == 1) {
           while (1) {
               appendNum(ans->decimal, newNumNode(now1->num), 1);
               freed1 = now1;
               now1 = now1->next;
               free(freed1);
               if (now1 == NULL) break;
           }
       }
       else if (check == 2) {
           while (1) {
               appendNum(ans->decimal, newNumNode(-now2->num), 1);
               freed2 = now2;
               now2 = now2->next;
               free(freed2);
               if (now2 == NULL) break;
           }
       }
   }
    check = 0;
    
    //정수 빼기 
    now1 = getNumNodeTail(n1->integer);
    now2 = getNumNodeTail(n2->integer);
    
    while(1) {
        if (now1 == NULL && now2 == NULL) break;
        else if (now1 == NULL) {
            check = 2;
            break;
        }
        else if (now2 == NULL) {
            check = 1;
            break;
        }
        
        appendNum(ans->integer, newNumNode(now1->num - now2->num), 0);
        freed1 = now1;
        freed2 = now2;
        now1 = now1->prev;
        now2 = now2->prev;
        free(freed1);
        free(freed2);
    }
    
    if (check == 1) {
        while (1) {
            appendNum(ans->integer, newNumNode(now1->num), 0);
            freed1 = now1;
            now1 = now1->prev;
            free(freed1);
            if (now1 == NULL) break;
        }
    }
    else if (check == 2) {
        while (1) {
            appendNum(ans->integer, newNumNode(-now2->num), 0);
            freed2 = now2;
            now2 = now2->prev;
            free(freed2);
            if (now2 == NULL) break;
        }
    }
    
    numNode *temp = ans->integer->head;
    
    // ans의 부호 정하기 
    while (1) {
        if (temp == NULL) {
            signChange = -1;
            break;
        }
        if (temp->num < 0) {
            signChange = 1;
            break;
        }
        else if (temp->num > 0) {
            signChange = 0;
            break;
        }
        temp = temp->next;
    }
    
    if (signChange == -1) {
        temp = ans->decimal->head;
        while (1) {
            if (temp == NULL) {
                signChange = 0;
                break;
            }
            if (temp->num < 0) {
                signChange = 1;
                break;
            }
            else if (temp->num > 0) {
                signChange = 0;
                break;
            }
            temp = temp->next;
        }
    }
    
    // ans의 부호에 따라 다른 방식으로 빼기 수행
    if (signChange) {
        ans->sign = (n1->sign + 1) % 2;
        if (ans->decimal->head) {
           temp = getNumNodeTail(ans->decimal);
           while (1) {
               if (temp == NULL) break;
               if (temp->num < 0) {
                   temp->num = -temp->num + chopping;
                   chopping = 0;
               }
               else if (temp->num > 0) {
                   temp->num = 10 - temp->num + chopping;
                   chopping = -1;
               }
               else if (temp->num ==0) {
                   if (chopping == -1) {
                       temp->num = 9;
                   }
               }
               temp = temp->prev;
           }
       }
        
        temp = getNumNodeTail(ans->integer);
        while (1) {
            if (temp == NULL) break;
            if (temp->num < 0) {
                temp->num = -temp->num + chopping;
                chopping = 0;
            }
            else if (temp->num > 0) {
                temp->num = 10 - temp->num + chopping;
                chopping = -1;
            }
            else if (temp->num ==0) {
                if (chopping == -1) {
                    temp->num = 9;
                }
            }
            temp = temp->prev;
        }
    }
    else if (!signChange) {
        ans->sign = n1->sign;
        if (ans->decimal->head) {
           temp = getNumNodeTail(ans->decimal);
           while (1) {
               if (temp == NULL) break;
               if (temp->num < 0) {
                   temp->num = temp->num + 10 + chopping;
                   chopping = -1;
               }
               else if (temp->num > 0) {
                   temp->num = temp->num + chopping;
                   chopping = 0;
               }
               else if (temp->num ==0) {
                   if (chopping == -1) {
                       temp->num = 9;
                   }
               }
               temp = temp->prev;
           }
       }
        temp = getNumNodeTail(ans->integer);
        while (1) {
            if (temp == NULL) break;
            if (temp->num < 0) {
                temp->num = temp->num + 10 + chopping;
                chopping = -1;
            }
            else if (temp->num > 0) {
                temp->num = temp->num + chopping;
                chopping = 0;
            }
            else if (temp->num ==0) {
                if (chopping == -1) {
                    temp->num = 9;
                }
            }
            temp = temp->prev;
        }
        
    }
    
    return ans;
}

// NUM 두 개를 인자로 받아 두 수를 곱한 값이 저장된 NUM을 리턴해주는 메서드 
NUM *multiply(NUM *n1, NUM *n2)
{
      // ans - 곱하기의 결과값 , multiplied -  정수 또는 소수 부분을 따로 계산, 중간계산 값 저장 
      
   NUM *ans = newNUM();
   numList *multiplied = newNumList();
    
    // 입력받은 두 수의 부호가 다르면 결과값은 음수 
    if (n1->sign != n2->sign) ans->sign = 0;
      
      /*
      multiplied 는 정수 또는 음수의 길이+1 만큼 0으로 초기화
   ans는 n1,n2의 정수부분, 소수부분의 자리수의 합만큼 -1로 초기화 
      */ 
      numNode *checkSize = n1->integer->head;
   
      while (checkSize) {
         appendNum(multiplied, newNumNode(0), 0);
         appendNum(ans->integer, newNumNode(-1), 0);
         checkSize = checkSize->next;
      }
   
   if (n1->decimal->head) {
         checkSize = n1->decimal->head;
         if (checkSize) {
            
            while (checkSize) {
               appendNum(multiplied, newNumNode(0), 0);
               appendNum(ans->decimal, newNumNode(-1), 0);
               checkSize = checkSize->next;
            }
      }
   }
   
      checkSize = n2->integer->head;
   
      while (checkSize) {
       appendNum(ans->integer, newNumNode(-1), 0);
         checkSize = checkSize->next;
      }
   
      if (n2->decimal->head) {
         checkSize = n2->decimal->head;
   
         while (checkSize) {
            appendNum(ans->decimal, newNumNode(-1), 0);
            checkSize = checkSize->next;
         }
   }
      appendNum(multiplied, newNumNode(0), 0);
    
   // n1,n2를 소수점 구분 없이 하나의 숫자배열로 만들기  
      if (n1->decimal->head) {
         numNode *temp1 = getNumNodeTail(n1->integer);
         temp1->next = n1->decimal->head;
         n1->decimal->head->prev = temp1;
   }
      
      if(n2->decimal->head) {
         numNode *temp2 = getNumNodeTail(n2->integer);
         temp2->next = n2->decimal->head;
         n2->decimal->head->prev = temp2;
   }
      
     int ceiling = 0;
      
      // " n2의 Tail * n1 " 식의 곱셈 수행 
      numNode *now1;
      numNode *now2 = getNumNodeTail(n2->integer);
   
      // 연산 결과값 저장 - 소수점 X 
      numList *ansTemp = newNumList();
      
      while (now2) {
       now1 = getNumNodeTail(n1->integer);
         numNode *temp = getNumNodeTail(multiplied);
         while(now1) {
           int n = temp->num + now1->num * now2->num + ceiling;
           temp->num = n % 10;
           ceiling = n / 10;
            temp = temp->prev;
            now1 = now1->prev;
         }
         temp->num = ceiling;
         ceiling = 0;
         
         // n2의 맨 앞에 도달했을 때 
         if(now2->prev == NULL) {
            temp = getNumNodeTail(multiplied);
           while (temp) {
               appendNum(ansTemp, newNumNode(temp->num), 0);
               numNode *freeed = temp;
               temp = temp->prev;
               free(freeed);
          }
          
         break;
      }
         
         // multiplied의 일의 자리를 ans에 append
      // 한 자리씩 계산하면 multiplied의 Tail은 고정된 수가 되기 때문
      // 이런 식으로 모든 자리수를 계산하여 답을 구할 수 있음 
       numNode *deleted = getNumNodeTail(multiplied);
       appendNum(ansTemp, newNumNode(deleted->num), 0);
       appendNum(multiplied, newNumNode(0), 0);
       deleted->prev->next = NULL;
       free(deleted);
         
         // 다음 자리 연산 준비 
       numNode *freed = now2;
       now2 = now2->prev;
       now2->next = NULL;
       free(freed); 
      }
   
   // ansTemp를 ans로 옮기기 
      numNode *src = getNumNodeTail(ansTemp);
      numNode *dpt;
   
      // ans의 decimal에 append(0) 
      if (ans->decimal->head) {
         dpt = getNumNodeTail(ans->decimal);
   
         while (dpt) {
            numNode *freed = src;
            dpt->num = src->num;
            src = src->prev;
            dpt = dpt->prev;
            free(freed);
         }
   }
      
      // integer에 append(0) 
      dpt = getNumNodeTail(ans->integer);
   
      while (dpt) {
       numNode *freed = src;
         dpt->num = src->num;
         src = src->prev;
         dpt = dpt->prev;
         free(freed);
      }
   
      free(checkSize);
      free(now1); free(now2);
      free(src);  free(dpt);
      free(ansTemp);   
   
      return ans;
}

//	postfix에 저장된 식 연산해주는 메서드 
NUM *calculate(expressionList *postfix)
{
	
   numStack *stack = newNumStack();
   while (1) {
   	// postfix 연산 - 숫자일때
      if (!postfix->head->oper) {
           pushToNumStack(stack, newNumStackNode(postfix->head->num));
           deleteHeadExpressionNode(postfix);
         }
         // postfix 연산 - 숫자일때
         else {
           char oper = postfix->head->oper;
           deleteHeadExpressionNode(postfix);
           if (oper == '+') {
               NUM *n2 = popFromNumStack(stack);
               NUM *n1 = popFromNumStack(stack);
               if (n1->sign == n2->sign) {
                  pushToNumStack(stack, newNumStackNode(add(n1, n2)));
            }
            else {
               pushToNumStack(stack, newNumStackNode(substract(n1, n2)));
            }
               free(n1); free(n2);
           }
           else if (oper == '-') {
              NUM *n2 = popFromNumStack(stack);
              NUM *n1 = popFromNumStack(stack);
              if (n1->sign == n2->sign) {
                 pushToNumStack(stack, newNumStackNode(substract(n1, n2)));   
            }
            else {
               pushToNumStack(stack, newNumStackNode(add(n1, n2)));
            }
               free(n1); free(n2);
           }
           else if (oper == '*') {
           	NUM *n2 = popFromNumStack(stack);
           	NUM *n1 = popFromNumStack(stack);
           	pushToNumStack(stack, newNumStackNode(multiply(n1, n2)));
		   }
         }
         if (postfix->head == NULL) break;
         }
   return popFromNumStack(stack);
}

//	NUM의 앞뒤 불필요한 0을 제거해주는 메서드 
void cleansing(NUM *n){
    numList *integer = n->integer;
    numList *decimal = n->decimal;
   
    while (integer->head->next != NULL && integer->head->num == 0) {
         numNode *temp = integer->head->next;
         temp->prev = NULL;
         free(integer->head);
         integer->head = temp;
    }
    if (decimal->head != NULL) {
      
       numNode *temp = getNumNodeTail(decimal);
      
       while (temp->num == 0) {
          if (temp->prev == NULL) {
            free(temp);
            decimal->head = NULL;
            break;
          }
          else {
             temp = temp->prev;
             free(temp->next);
             temp->next = NULL;
         }
      }
   }
}
