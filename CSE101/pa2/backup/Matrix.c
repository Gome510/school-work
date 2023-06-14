 //Pablo Gomez-Echegaray
//pgomezec
//pa2

#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"
#include<string.h>
#include "List.h"

//Matrix ADT
typedef struct MatrixObj{
   int nze;
   int size;
   List *row;
   
} MatrixObj;
typedef MatrixObj* Matrix;

typedef struct EntryObj{
	int col;
	double entry;
} EntryObj;
typedef EntryObj* Entry;

//-Constructor & Destructors

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
	Matrix M = (malloc(sizeof(MatrixObj)));
	M->row = (malloc(sizeof(ListObj)*(n+1)));
	M->nze = 0;
	M->size = n;
    
    for(int i = 1; i<=n;i++){
        M->row[i] = newList();
    }
    
	return(M);
}
// newEntry() - returns a reference to a new Entry object.
Entry newEntry(int col, double entry){
	Entry E = (malloc(sizeof(EntryObj)));
	E->col = col;
	E->entry = entry;
	return(E);
}
// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    if(*pM==NULL){
        return;
    }
	int n = (*pM)->size;
	for(int i =1; i<=n; i++){
		freeList(&((*pM)->row[i]));
	}
	free((*pM)->row);
	(*pM)->row = NULL;
	free(*pM);
	*pM = NULL;
}
// freeEntry()
// Frees heap memory associated with *pE, sets *pE to NULL.
void freeEntry(Entry* pE){
    if(*pE==NULL){
        return;
    }
	free(*pE);
	*pE = NULL;
}

//-Access functions

// size()
// Return the size of square Matrix M.
int size(Matrix M){
	if(M==NULL){
        printf("Matrix Error: size(Matrix G) called where M==NULL");
        exit(1);
    }else{
        return M->size;
    }
	
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
	if(M==NULL){
        printf("Matrix Error: NNZ(Matrix G) called where M==NULL");
        exit(1);
    }else{
        return M->nze;
    }
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
        if (A == NULL){
        printf("Matrix Error: equalsEntry(Matrix G) called where A==NULL");
        exit(1);
    }
    if (B == NULL){
        printf("Matrix Error: equalsEntry(Matrix G) called where B==NULL");
        exit(1);
    }
    return 0;
}

// equalsEntry()
// Return true (1) if entries A and B are equal, false (0) otherwise.
int equalsEntry(Entry A, Entry B){
    if (A == NULL){
        printf("Matrix Error: equalsEntry(Matrix G) called where A==NULL");
        exit(1);
    }
    if (B == NULL){
        printf("Matrix Error: equalsEntry(Matrix G) called where B==NULL");
        exit(1);
    }
    
    if((A->entry == B->entry)&&(A->col == B->col)){
        return 1;
    }else{
        return 0;
    }
}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M){
    if (M == NULL){
        printf("Matrix Error: makeZero(Matrix M) called where M==NULL");
        exit(1);
    }
    int n = M->size;
    for(int i=1; i<=n; i++){//clears all non-zero entries in each row(list).
        clear(M->row[i]);
    }
    M->nze = 0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
 // changes ith row, jth column of this Matrix to x
 // pre: 1<=i<=size(M), 1<=j<=size(M)
    if(M==NULL){
        printf("Matrix Error: made call to changeEntry() while M == NULL");
        exit(1);
    }
    if((1<=i && i<=size(M)) && (1<=j && j<=size(M))){//pre: 1<=i<=size(M), 1<=j<=size(M)
        
        moveFront(M->row[i]);
        if (M->row[i]->cursor==NULL){//if the list is empty
            //System.out.println("row[i-1].cursor==NULL");
            if(x==0.0)return;//if you want to put a zero into MY MATRIX, you're wasting my space so don't bother.
            //Entry E2 = newEntry(j,x);//>>malloc<<
            //Entry* E = &E2;
            append(M->row[i], newEntry(j,x));
            //printf("isEmpty(M->row[1]): %s\n", isEmpty(M->row[1])?"true":"false" );
            
            M->nze++;
            return;
        }
        while(M->row[i]->cursor!=NULL){
            Entry E2 = (Entry)get(M->row[i]); // maybe I need to keep it as a pointer.
            if(E2->col==j){//if the entry exists
                if(E2->entry==0.0 && (x !=0.0)){// ZE -> NZE
                    M->nze++;
                    E2->entry = x;
                    //row[i-1].get() = E2;
                    break;
                }
                if(x ==0.0){//turning into a zero entry
                    M->nze--;
                    delete(M->row[i]);
                    break;
                }
                E2->entry = x;//NZE -> NZE
                //row[i-1].get() = E2;
                break;
            }
            if(E2->col>j){//if the entry is missing from the inside of the list
                //System.out.println("insertingBefore to list");
                if(x !=0.0){
                    M->nze++;
                }else{
                    break;
                }
                Entry E3 = newEntry(j,x);//>>malloc<<
                insertBefore(M->row[i], E3);
                break;
            }
            if(index(M->row[i])==length(M->row[i])-1){// if the entry belongs in the end of the list.
                if(x !=0.0){
                    M->nze++;
                }else{
                    break;
                }
                Entry E3 = newEntry(j,x);//>>malloc<<
                append(M->row[i], E3);
                break;
            }
            else{
                moveNext(M->row[i]);
            }
        }
        //row[i-1].cursor = L;
    }else{
        //throw new RuntimeException("Matrix Error: made call to changeEntry() while i or j was < 1 or > size.");
        printf("Matrix Error: made call to changeEntry() while i or j was < 1 or > size.");
        exit(1);
    }   
}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    int tn = size(A);
    Matrix N = newMatrix(tn);//>>malloc<<
    //System.out.println("N size:"+tn);
    for(int i=1;i<=tn;i++){//for each row
        moveFront(A->row[i]);
        moveFront(N->row[i]);
        while(A->row[i]->cursor!=NULL){//for each entry in each row
            
            //do we need the following if statement->
            //if(back(A->row[i]) instanceof Entry){// if the objects we are copying are 
                Entry E2 = (Entry)back(A->row[i]);
                //Entry E2 = *E1;
                changeEntry(N, i, E2->col, E2->entry);
            //}
            //N.row[i].length++;
            moveNext(A->row[i]);
        }
    }
    N->nze = A->nze;
    return N;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    if(A==NULL){
        printf("Matrix Error: made call to scalarMult() while A == NULL");
        exit(1);
    }
    Matrix P = newMatrix(size(A));//>>malloc<<
    return P;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    if(A==NULL){
        printf("Matrix Error: made call to scalarMult() while A == NULL");
        exit(1);
    }
    Matrix P = newMatrix(size(A));//>>malloc<<
    return P;
    
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    if(A==NULL || B==NULL){
        printf("Matrix Error: made call to sum() while M == NULL");
        exit(1);
    }
    if(size(A)==size(B)){//if preconditions are met
        Matrix P = newMatrix(size(A));//>>malloc<<
        return P;
        
    }else{
        printf("Matrix Error: made call to sum() while size(A)!=size(B)");
        exit(1);
    }
    
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    if(A==NULL || B==NULL){
        printf("Matrix Error: made call to sum() while M == NULL");
        exit(1);
    }
    if(size(A)==size(B)){//if preconditions are met
        Matrix P = newMatrix(size(A));//>>malloc<<
        return P;
        
    }else{
        printf("Matrix Error: made call to sum() while size(A)!=size(B)");
        exit(1);
    }
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    if(A==NULL || B==NULL){
        printf("Matrix Error: made call to sum() while M == NULL");
        exit(1);
    }
    if(size(A)==size(B)){//if preconditions are met
        Matrix P = newMatrix(size(A));//>>malloc<<
        return P;
        
    }else{
        printf("Matrix Error: made call to sum() while size(A)!=size(B)");
        exit(1);
    }
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    
    int n = M->size;
    //System.out.println("I want to print a matrix of size "+n);
    for (int i = 1; i<=n; i++){
        int nzr = 0;
        moveFront(M->row[i]);
        if (isEmpty(M->row[i])){//if the row is empty, skip it.
            continue;
            //System.out.println("row[i].cursor==null")
        }
        while(M->row[i]->cursor!=NULL){//If this a non-zero row, print the row number.
            //System.out.println("    ay");
            Entry TE = (Entry)get(M->row[i]);
            if (TE->entry!=0.0){
                fprintf(out, "%d: ",i+1);
                nzr = 1;
                break;
            }else{
                moveNext(M->row[i]);
            }
        }
        //System.out.println();
        if(nzr==0){
            //System.out.println(" But this is a zero row"); 
            continue;
        }
        //str+=(row[i]+"\n");//call List.toString
        printRow(out, M, i);
    }
    
    return;
}
// printList()
// Prints data elements in Q on a single line to output file.
void printRow(FILE* out, Matrix M, int i){
   if( M==NULL ){
      printf("Matrix Error: calling printRow() on NULL Matrix reference\n");
      exit(1);
   }
   if( M->row[i]==NULL ){
      printf("Matrix Error: calling printRow() on NULL List reference of a row\n");
      exit(1);
   }
   //printf("Q->front: %d\n", Q->front->index);
   Node N = NULL;
   //int Qlen = length(Q);
   //char Qdata[2200]="";
   //printf("%s\n",Qdata);
   for(N = M->row[i]->front; N != NULL; N = N->next){
      Entry x = (Entry)N->index; // do i need to change to void*?
      //char str[100];
      fprintf(out, "(%d, %f) ",x->col,x->entry);
      /*if(N->next!=NULL){
         sprintf(str, "%f ", *x);
         strcat(Qdata, str);
         
      }else{
         sprintf(str, "%f", *x);
         strcat(Qdata, str);
      }*/
   }
   //printf("%s\n", Qdata);
   //fprintf(out, "%s\n", Qdata);
}


