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
    
    for(int i = 0; i<=n;i++){
        G->adjList[i] = newList();
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
	for(int i =0; i<=n; i++){
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
    for(int i=0; i<=n; i++){//clears all non-zero entries in each row(list).
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
            Entry* E = &(newEntry(j,x));
            append(M->row[i], E);
            M->nze++;
            return;
        }
        while(M->row[i]->cursor!=NULL){
            Entry E2 = *(Entry*)get(row[i]); // maybe I need to keep it as a pointer.
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
                Entry E3 = newEntry(j,x);
                insertBefore(M->row[i], E3);
                break;
            }
            if(index(M->row[i])==length(M->row[i])-1){// if the entry belongs in the end of the list.
                if(x !=0.0){
                    this.nze++;
                }else{
                    break;
                }
                Entry E3 = newEntry(j,x);
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
    int tn = size(M);
    Matrix N = newMatrix(tn);
    //System.out.println("N size:"+tn);
    for(int i=0;i<=tn;i++){//for each row
        moveFront(M->row[i]);
        moveFront(N->row[i]);
        while(M->row[i]->cursor!=NULL){//for each entry in each row
            
            if(M->row[i].back() instanceof Entry){// if the objects we are copying are 
                Entry E1 = (Entry) row[i].back();
                N.changeEntry(i+1, E1.col, E1.entry);
            }
            //N.row[i].length++;
            row[i].moveNext();
        }
    }
    N.nze = this.nze;
    return N;

}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A);

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A);

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B);

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B);

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M);



