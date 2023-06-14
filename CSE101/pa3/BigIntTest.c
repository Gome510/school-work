//Pablo Gomez-Echegaray
//pgomezec
//pa3 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "BigInteger.h"
int main(int argc, char* argv[]){
        if(argc != 3){//check command line for correct number of arguments
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    
    FILE *in, *out;
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    
    if(in==NULL){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if(out==NULL){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
//-------Reading---------------------------------------------------------------
    char bA[100];
    char bB[100];
    fprintf(stdout,"-----Input file-----\n");
    //fscanf(in, "%s", bA);
    fgets(bA,100,in);
    int a = atoi(bA);
    fprintf(stdout, "%d\n", a); //print number of digits in A
    char intA[a+5];
   
    fgets(intA, sizeof(intA), in);
    //fscanf(in,"%s",intA);
    fprintf(stdout, "%s\n", intA);//print int A
    
    fgets(bB, 100, in);
    //fscanf(in,"%s",bB);
    int b = atoi(bB);
    fprintf(stdout,"%d\n", b); //print number of digits in B
    char intB[b+5];
    fgets(intB, sizeof(intB), in);
    //fscanf(in, "%s\n",intB);
    fprintf(stdout,"%s\n",intB); //print int B
    printf("-----Computing-----\n");

//-------Computing-------------------------------------------------------------    
   BigInteger A = stringToBigInteger(intA);
   BigInteger B = stringToBigInteger(intB);
   BigInteger C = newBigInteger();
   
   printBigInteger(out, A);//+
   printBigInteger(out, B);//+
   printBigInteger(out, C);//0
   //printf("Is A->integer empty? %d\n", A->integer->front==NULL );
   
  
   /*
   add(C,A,A);//(+)+(+)
   printBigInteger(out, B);//A
    
   negate(A);//(+)+(-)
   add(A,C,A);//A=-A //Call
   printBigInteger(out, A);//-A
   
   //(-)+(+)
   add(A,A,C);//A=-A //Call
   printBigInteger(out, A);//-A
   
   //(-)+(-)
   add(A,A,A);//A=-A
   printBigInteger(out, A);//-A
   */
   printf("***Compare Test:***\n");
   //negate(A);
   printf(" (A) vs (B) : %d\n",compare(A,B));
   
   negate(B);
   printf(" (A) vs (-B): %d\n", compare(A,B));
   
   negate(B);
   negate(A);
   printf(" (-A) vs (B): %d\n", compare(A,B));
   
   negate(B);
   printf(" (-A) vs (-B): %d\n", compare(A,B));
   
   printf("***Add Test:***\n");
   add(C,A,B);//C=A //A+0
   printBigInteger(out, C);//-(A+B)
   
   negate(A);
   negate(B);
   add(C,A,B);//C=A //A+0
   printBigInteger(out, C);//A+B
   
   printf("***Subtract Test:***\n");
   
   subtract(C,A,B);
   printBigInteger(out, C);//A-B
   
   negate(A);
   negate(B);
   subtract(C,A,B);//C=A //A+0
   printBigInteger(out, C);//-A-(-B)
   
   printf("***Grading Test:***\n");
   
   BigInteger *pA;
   //,*pC, *pD;
   pA = NULL;
   //pC = NULL;
   //pD = NULL;
   pA = malloc(sizeof(BigInteger));
   *pA = newBigInteger();
   if (sign(*pA) != 0) printf("pA->sign != 0 <<<\n");
   /*
   *pC = stringToBigInteger("+13378008135");
   *pD = stringToBigInteger("-13378008135"); */
   //if(sign(*pC) != 1 || sign(*pD) != -1) printf("pC or pD->sign is incorrect <<<\n");
   freeBigInteger(pA);
   free(pA);
   //freeBigInteger(pD);
   
   printf("\n***Sub Test:***\n");
   subtract(C,A,B);
   printBigInteger(C);

   freeBigInteger(&A);
   freeBigInteger(&B);
   freeBigInteger(&C);
    
    
//-----------------------------------------------------------------------------
    fclose(in);
    fclose(out);
}
