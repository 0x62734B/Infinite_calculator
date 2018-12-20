#include "calculator.h"

// NUM �� ���� ���ڷ� �޾� �� ���� ���� ���� ����� NUM�� �������ִ� �޼��� 
NUM *add(NUM *n1, NUM *n2)
{
	//  ceiling - ���� �� �ڸ����� �Ѿ�� ���� �ڸ����� ������ �� 
	//	check - NUM�� ����,�Ҽ��κ�  ���� ���� 
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
      
      // ������ �ڸ����� ������ 
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
      
      // �Ҽ� ����Ʈ�� Tail�� ����Ŵ 
      numNode *temp = getNumNodeTail(ans->decimal);
      
      // NumNode �� �Ҽ��κ���  num�� ��� �� �ڸ� �ڿ����� �ǵ��� ���� 
      while (1) {
         int n = temp->num + ceiling;
         temp->num =  n % 10;
         ceiling = n / 10;
         temp = temp->prev;
         if (temp == NULL) break;
      }
   }
   
    //	���� ó�� �غ� (1�� �ڸ����� ���� ����) 
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
   
   //	�ѱ�� ���� �����ϴ� ������ �ڸ����� ũ�� �տ��� ceiling�� append
   if (ceiling) appendNum(ans->integer, newNumNode(ceiling), 0);
   
   return ans;
}

// NUM �� ���� ���ڷ� �޾� �� ���� �� ���� ����� NUM�� �������ִ� �޼���
NUM *substract(NUM *n1, NUM *n2) 
{
	
	// chopping - ceiling�� ���� ���� 
	// signchange - num�� ��ȣ ���� 
    int check = 0, chopping = 0, signChange = 0;
    NUM *ans = newNUM();
    
    //�Ҽ��� ���� 
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
    
    //���� ���� 
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
    
    // ans�� ��ȣ ���ϱ� 
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
    
    // ans�� ��ȣ�� ���� �ٸ� ������� ���� ����
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

// NUM �� ���� ���ڷ� �޾� �� ���� ���� ���� ����� NUM�� �������ִ� �޼��� 
NUM *multiply(NUM *n1, NUM *n2)
{
      // ans - ���ϱ��� ����� , multiplied -  ���� �Ǵ� �Ҽ� �κ��� ���� ���, �߰���� �� ���� 
      
   NUM *ans = newNUM();
   numList *multiplied = newNumList();
    
    // �Է¹��� �� ���� ��ȣ�� �ٸ��� ������� ���� 
    if (n1->sign != n2->sign) ans->sign = 0;
      
      /*
      multiplied �� ���� �Ǵ� ������ ����+1 ��ŭ 0���� �ʱ�ȭ
   ans�� n1,n2�� �����κ�, �Ҽ��κ��� �ڸ����� �ո�ŭ -1�� �ʱ�ȭ 
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
    
   // n1,n2�� �Ҽ��� ���� ���� �ϳ��� ���ڹ迭�� �����  
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
      
      // " n2�� Tail * n1 " ���� ���� ���� 
      numNode *now1;
      numNode *now2 = getNumNodeTail(n2->integer);
   
      // ���� ����� ���� - �Ҽ��� X 
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
         
         // n2�� �� �տ� �������� �� 
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
         
         // multiplied�� ���� �ڸ��� ans�� append
      // �� �ڸ��� ����ϸ� multiplied�� Tail�� ������ ���� �Ǳ� ����
      // �̷� ������ ��� �ڸ����� ����Ͽ� ���� ���� �� ���� 
       numNode *deleted = getNumNodeTail(multiplied);
       appendNum(ansTemp, newNumNode(deleted->num), 0);
       appendNum(multiplied, newNumNode(0), 0);
       deleted->prev->next = NULL;
       free(deleted);
         
         // ���� �ڸ� ���� �غ� 
       numNode *freed = now2;
       now2 = now2->prev;
       now2->next = NULL;
       free(freed); 
      }
   
   // ansTemp�� ans�� �ű�� 
      numNode *src = getNumNodeTail(ansTemp);
      numNode *dpt;
   
      // ans�� decimal�� append(0) 
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
      
      // integer�� append(0) 
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

//	postfix�� ����� �� �������ִ� �޼��� 
NUM *calculate(expressionList *postfix)
{
	
   numStack *stack = newNumStack();
   while (1) {
   	// postfix ���� - �����϶�
      if (!postfix->head->oper) {
           pushToNumStack(stack, newNumStackNode(postfix->head->num));
           deleteHeadExpressionNode(postfix);
         }
         // postfix ���� - �����϶�
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

//	NUM�� �յ� ���ʿ��� 0�� �������ִ� �޼��� 
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
