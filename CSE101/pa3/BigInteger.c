//Pablo Gomez-Echegaray
//pgomezec
//pa3
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BigInteger.h"
#include "List.h"
#define POWER 9
#define BASE 1000000000
typedef struct BigIntegerObj{
   int sign;
   struct ListObj* integer;
} BigIntegerObj;

typedef BigIntegerObj* BigInteger;

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(){
   BigInteger B = malloc(sizeof(BigIntegerObj));
   B->integer = newList();
   B->sign = 0;
   return B;
}
// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* B){
   //if(B!=NULL && *B!=NULL) { 
      freeList(&((*B)->integer));
      (*B)->integer = NULL;
      free(*B);
   //}
   B=NULL;
}

// Access functions -----------------------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){
   if(s==NULL){
      printf("BigInteger Error: called stringToBigInteger() when s was equal to NULL");
      exit(EXIT_FAILURE);
   }
   BigInteger B = newBigInteger();
   char SN = (char)(s[0]);
   printf("sign = '%c': %d\n",SN, SN=='-');
   if(SN == '-'){//If optional negative sign was included
      B->sign = -1;
      s[0] = '0';
   }else if(SN == '+'){//if optional postitive sign was included
      B->sign = 1;
      s[0] = '0';//subtract the sign char from the string so it can be turned to a number.
   }
   int length = strlen(s);
   printf("sizeof(s) = %d\n", length);
   
   int i;
   for(i=length-2; i>=0;i=i-POWER){//extracting base 10^9 numbers
      char d[9]="         ";
      int k = 8;
      for(int j = i; j>i-POWER && j>=0; j--){//extract this base 10^9 number from the big integer.
         d[k] = (char)s[j];
         k--;
      }
      long x = 0;
      x = (long)atoi(d);
      if((B->sign == 0) && (x!=0)){
         B->sign = 1;
      }
      //printf("%s = %ld\n", d, x);
      printf("%s\n", d);
      prepend(B->integer,x);
   }
   
   return B;
}
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
   if(N!=NULL){ 
      clear(N->integer);
      N->sign =0;
   }else{
      printf("BigInteger Error: called makeZero() when N was equal to NULL");
      exit(1);
   }
}
// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N){
   if(N!=NULL) {
      return N->sign;
   }else{
      printf("BigInteger Error: called sign() when N was equal to NULL");
      exit(1);
   }
}
/*
int base(BigInteger N){
   if(N!=NULL) {
      return N->p;
   }else{
      printf("BigInteger Error: called base() when N was equal to NULL");
      exit(1);
   }
}*/

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
   if(A!=NULL && B!=NULL) {
      Node Ca = A->integer->back;//1
      Node Cb = B->integer->back;//-1
      int larger = 0;//0 for equal.
      //Node Cb = B->integer->cursor;
      for(Cb = B->integer->back; Ca != NULL && Cb != NULL; Ca = Ca->prev){
         if( Ca->index == Cb->index ){
            
         }else if( Ca->index > Cb->index){
            larger = 1;
         }else{
            larger = -1;
         }
         if(Ca->prev == NULL && Cb->prev == NULL){
            
         }else if((Ca->prev==NULL) ^ (Cb->prev==NULL)){
            if(Ca->prev == NULL){
               larger = 1;
            }else{
               larger =-1;
            }
         }
         Cb = Cb->prev;
      }
      //if one of them is zero or wrongly larger.
      if(A->sign > B->sign && larger <= 0){
         larger = 1;
      }
      if(A->sign < B->sign && larger >= 0){
         larger =-1;
      }
      return larger;
      
   }else{
      printf("BigInteger Error: called compare() when A or B was equal to NULL");
      exit(1);
   }   
}
// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
   if(N==NULL){
      printf("BigInteger Error: called add() when N was equal to NULL");
      exit(EXIT_FAILURE);
   }
   BigInteger C = newBigInteger();
   C->sign = N->sign;
   C->integer = copyList(N->integer);
   return C;
}
void overwrite(BigInteger S, BigInteger N){//Makes S into a clone of N by overwriting S data with N data.
   if(S==NULL || N==NULL){
      printf("BigInteger Error: called add() when S or N were equal to NULL");
      exit(EXIT_FAILURE);
   }
   S->sign = N->sign;
   List H = S->integer;
   S->integer = copyList(N->integer);
   freeList(&(H));
}
// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N){
   if(N==NULL){
      printf("BigInteger Error: called negate() when N was equal to NULL");
      exit(EXIT_FAILURE);
   }
   N->sign = (N->sign)*-1;
} 
// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
// S = S + S must be possible
void add(BigInteger S, BigInteger A, BigInteger B){
   if((S==NULL || A==NULL) || B==NULL){
      printf("BigInteger Error: called add() when S, A, or B were equal to NULL");
      exit(EXIT_FAILURE);
   }
   if(A->sign ==0 || B->sign == 0){//if either are zero, then do less work.
      printf("A or B = 0 --> ");
      if(A->sign ==0){
         printf("A = 0\n");
         overwrite(S, B);
      }else if(B->sign ==0){
         printf("B = 0\n");
         overwrite(S, A);
      }
      return;
   }
//if they are both non-zero.
   if (A->sign == 1){
      printf("A = +1 --> ");
      if (B->sign == 1){
         printf("B = +1. adding...\n");
         addhelp(S,A,B);
         Normalize(S);
          S->sign = 1;
         return;
      }
      if (B->sign == -1){
         printf("B = -1. Calling sub(S,A,-B)\n");
         negate(B);
         subtract(S,A,B);
         negate(B);
         return;
      }
   }else{//A must be negative since it's not pos or zero.
      if(A->sign == -1){
         printf("A = -1 --> ");
      }else{
         printf("Somehow! A = %d --> ",A->sign);
      }//just checking if A->sign == -1
      
      if (B->sign == 1){//-A+B = B - A
         printf("B = +1. Calling sub(S,B,A)\n");
         negate(A);
         subtract(S,B,A);
         negate(A);
         return;
      }
      if (B->sign == -1){
         printf("B = -1. adding...\n");
         addhelp(S,A,B);
         Normalize(S);
         S->sign = -1;
         return;
      }
   }
}
void addhelp(BigInteger S, BigInteger A, BigInteger B){
   //Determines the magnitude of S. Sign is assigned by add().
   Node pA = A->integer->back;
   Node pB = B->integer->back;
   BigInteger R = newBigInteger();
   while(pA != NULL && pB != NULL) {
      prepend(R->integer, pA->index + pB->index);
      
      pA=pA->prev;
      pB=pB->prev;
      
      if(pA==NULL || pB==NULL){
        if(pA==NULL && pB==NULL){
          break;
        }
        if(pA ==NULL){
          //add the rest of B
          while(pB!=NULL){
            prepend(R->integer, pB->index);
            pB= pB->prev;
          }
          break;
        }
        if(pB==NULL){
          //add the rest of A
          while(pA!=NULL){
            prepend(R->integer, pB->index);
            pA= pA->prev;
          }
          break;
        }
      }
   }
   overwrite(S, R);
   freeBigInteger(&R);
}
// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger S, BigInteger A, BigInteger B){
   if((S==NULL || A==NULL) || B==NULL){
      printf("BigInteger Error: called add() when S, A, or B were equal to NULL");
      exit(EXIT_FAILURE);
   }
   if(A->sign ==0 || B->sign == 0){//if either are zero, then do less work.
      printf("A or B = 0 --> ");
      if(A->sign ==0){
         printf("A = 0\n");
         overwrite(S, B);
         if(B->sign == 1){//0-(+B)=(-B)
            S->sign = -1;
         }
      }else if(B->sign ==0){
         printf("B = 0\n");
         overwrite(S, A);
      }
      return;
   }
//if they are both non-zero.
   if (A->sign == 1){
      printf("A = +1 --> ");
      if (B->sign == 1){
         printf("B = +1. subtracting...\n");
         subhelp(S,A,B);
         Normalize(S);
         
         return;
      }
      if (B->sign == -1){//A - (-B) = A + B
         printf("B = -1. Calling add(S,A,-B)\n");
         negate(B);
         add(S,A,B);
         negate(B);
         return;
      }
   }else{//A must be negative since it's not pos or zero.
      if(A->sign == -1){
         printf("A = -1 --> ");
      }else{
         printf("Somehow! A = %d --> ",A->sign);
      }//just checking if A->sign == -1
      
      if (B->sign == 1){//-A-B = (-A) + (-B)
         printf("B = +1. Calling add(S,B,A)\n");
         negate(B);
         add(S,A,B);
         negate(B);
         return;
      }
      if (B->sign == -1){//(-A)-(-B) = -(A-B)
         printf("B = -1. subtracting...\n");
         subhelp(S,A,B);
         Normalize(S);
         int c = compare(A,B);
         if(c == -1){ //if -A < -B -> (-A) - (-B) = -C
            S->sign = -1;
         }else{// if -A > -B -> (-A) - (-B) = +C
            S->sign = 1;
         }
         return;
      }
   }
}
void subhelp(BigInteger S, BigInteger A, BigInteger B){
   BigInteger R = newBigInteger();
   int c = compare(A,B);
   if( c == 0){
      overwrite(S, R);
      freeBigInteger(&R);
      return;
   }else if( c == -1){//if A<B -> (
      BigInteger X = A;
      A = B;
      B = X;
   }else{
      //A>B as we wanted.
   }   
   Node pA = A->integer->back;
   Node pB = B->integer->back;
   
   while(pA != NULL && pB != NULL) {
      prepend(R->integer, pA->index - pB->index);
      
      pA=pA->prev;
      pB=pB->prev;
      
      if(pA==NULL || pB==NULL){
        if(pA==NULL && pB==NULL){
          break;
        }
        if(pA ==NULL){
          //add the rest of B
          while(pB!=NULL){
            prepend(R->integer, pB->index);
            pB= pB->prev;
          }
          break;
        }
        if(pB==NULL){
          //add the rest of A
          while(pA!=NULL){
            prepend(R->integer, pB->index);
            pA= pA->prev;
          }
          break;
        }
      }
   }
   if(c==-1){// swap it back.
      BigInteger X = A;
      A = B;
      B = X;
   }
   overwrite(S, R);
   freeBigInteger(&R);
}

void Normalize(BigInteger A){
  Node pA = A->integer->back;
  while(pA!=NULL){
    if(pA->index >= BASE){//Carry out 
      long x = 0, r = 0;
       x = (long)((pA->index)/(BASE));//Carry out
       r = pA->index % BASE;//remainder
      if(pA->prev==NULL){//carry out to new node
        prepend(A->integer, x);
        pA->index = r;
        pA=pA->prev;
        continue;
      }else{//carry out to next node
        pA->prev->index = pA->prev->index + x;
        pA->index = r;
        pA=pA->prev;
        continue;
      }
    }
    if(pA->index < 0){//Borrow
      //long x = 0, y = 0;
      //x = ceil((pA->index)/(BASE));
      //y = pA->index % BASE;
      if( pA->index > -BASE){//if want to borrow only 1 
          if(pA->prev!=NULL){//if we have something to borrow from
            pA->index = pA->index + BASE;
            pA->prev->index = pA->prev->index -1;
            pA=pA->prev;
            continue;
          }
          if(pA->prev==NULL){//if we dont have something to borrow from
            pA->index=pA->index*(-1);
            A->sign= -1;
            /*
            if(pA->index <= -BASE){
              pA->index = pA->index - BASE;
              prepend(A->integer,1);
            }*/
            pA=pA->prev;
            continue;
          }
      }
        /* may not be necessary since multiplying pretends both "integers" are positive.
      if(pA->index <= -BASE){//if we're multiplying and we need to borrow more
          if(pA->next!=NULL){//if there is something to borrow from
            pA->index = pA->index + BASE;
            pA->next = pA->next->index -x;
            pA=pA->next;
            continue;
          }
          if(pA->next==NULL){//if there is nothing to borrow from
            pA->index=pA->index*(-1);
            A->sign= -1;
            if(pA->index <= -BASE){
              pA->index = pA->index - BASE;
              prepend(A->integer,1);
            }
            pA=pA->next;
            continue;
          }
      }*/
    }
    pA=pA->prev;
  }
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
   
   if(A==NULL || B==NULL){
      printf("BigInteger Error: called add() when S, A, or B were equal to NULL");
      exit(EXIT_FAILURE);
   }
   BigInteger S = newBigInteger();
   if(A->sign ==0 || B->sign == 0){//if either are zero, then do less work.
      printf("A or B = 0 --> ");
      if(A->sign ==0){
         printf("A = 0\n");
         overwrite(S, B);
      }else if(B->sign ==0){
         printf("B = 0\n");
         overwrite(S, A);
      }
      return S;
   }
//if they are both non-zero.
   if (A->sign == 1){
      printf("A = +1 --> ");
      if (B->sign == 1){
         printf("B = +1. adding...\n");
         addhelp(S,A,B);
         Normalize(S);
          S->sign = 1;
         return S;
      }
      if (B->sign == -1){
         printf("B = -1. Calling sub(S,A,-B)\n");
         negate(B);
         subtract(S,A,B);
         negate(B);
         return S;
      }
   }else{//A must be negative since it's not pos or zero.
      if(A->sign == -1){
         printf("A = -1 --> ");
      }else{
         printf("Somehow! A = %d --> ",A->sign);
      }//just checking if A->sign == -1
      
      if (B->sign == 1){//-A+B = B - A
         printf("B = +1. Calling sub(S,B,A)\n");
         negate(A);
         subtract(S,B,A);
         negate(A);
         return S;
      }
      if (B->sign == -1){
         printf("B = -1. adding...\n");
         addhelp(S,A,B);
         Normalize(S);
         S->sign = -1;
         return S;
      }
   }
   return S;
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B){
   
   if(A==NULL || B==NULL){
      printf("BigInteger Error: called add() when S, A, or B were equal to NULL");
      exit(EXIT_FAILURE);
   }
   BigInteger S = newBigInteger();
   if(A->sign ==0 || B->sign == 0){//if either are zero, then do less work.
      printf("A or B = 0 --> ");
      if(A->sign ==0){
         printf("A = 0\n");
         overwrite(S, B);
         if(B->sign == 1){//0-(+B)=(-B)
            S->sign = -1;
         }
      }else if(B->sign ==0){
         printf("B = 0\n");
         overwrite(S, A);
      }
      return S;
   }
//if they are both non-zero.
   if (A->sign == 1){
      printf("A = +1 --> ");
      if (B->sign == 1){
         printf("B = +1. subtracting...\n");
         subhelp(S,A,B);
         Normalize(S);
         
         return S;
      }
      if (B->sign == -1){//A - (-B) = A + B
         printf("B = -1. Calling add(S,A,-B)\n");
         negate(B);
         add(S,A,B);
         negate(B);
         return S;
      }
   }else{//A must be negative since it's not pos or zero.
      if(A->sign == -1){
         printf("A = -1 --> ");
      }else{
         printf("Somehow! A = %d --> ",A->sign);
      }//just checking if A->sign == -1
      
      if (B->sign == 1){//-A-B = (-A) + (-B)
         printf("B = +1. Calling add(S,B,A)\n");
         negate(B);
         add(S,A,B);
         negate(B);
         return S;
      }
      if (B->sign == -1){//(-A)-(-B) = -(A-B)
         printf("B = -1. subtracting...\n");
         subhelp(S,A,B);
         Normalize(S);
         int c = compare(A,B);
         if(c == -1){ //if -A < -B -> (-A) - (-B) = -C
            S->sign = -1;
         }else{// if -A > -B -> (-A) - (-B) = +C
            S->sign = 1;
         }
         return S;
      }
   }
   return S;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
   return;
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
   BigInteger P = newBigInteger();
   return P;
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
   if(compare(A,B)==0){
      return 1;
   }else{
      return 0;
   }
}

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){
   Node P = N->integer->front;
   if(N->sign == -1)fprintf(out,"-");
   
   int lead = 0;
   while(P!=NULL){
      if(P->index !=0 && lead ==0){
         lead = 1;
         fprintf(out,"%ld", P->index);
      }else if(lead == 1){
         long Pin = P->index;
         int n = POWER - ((int)(Log10(Pin))+1);
         //printf("(lz:%d)",n);
         for(int i =1; i<=n;i++){
            fprintf(out,"0");
         }
         fprintf(out,"%ld", P->index);
      }else{}
      P = P->next;
   }
   if(N->sign == 0)fprintf(out,"0");
   fprintf(out,"\n");
}

long Log10(long n){
   return (n>9) ? 1 + Log10(n / 10) : 0;
}




