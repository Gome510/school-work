//Pablo Gomez-Echegaray
//pgomezec
//pa2
//-----------------------------------------------------------------------------
// Queue.c
// Implementation file for Queue ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include<string.h>
// structs --------------------------------------------------------------------

// private NodeObj type
/*
typedef struct NodeObj{
   int index;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private QueueObj type
typedef struct List{
   Node front;
   Node back;
   Node cursor;
   int length;
} List;
*/

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(void* data){
   Node N = malloc(sizeof(NodeObj));
   N->index = data;
   N->next = NULL;
   N->prev = NULL;
   strcpy(N->line,"");
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      //free((*pN)->index);
      (*pN)->index = NULL;
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty Queue object.
List newList(void){
   List Q;
   Q = malloc(sizeof(ListObj));
   Q->front = Q->back = NULL;
   Q->length = 0;
   Q->cursor = NULL;
   return(Q);
}


// freeList()
// Frees all heap memory associated with List *pQ, and sets *pQ to NULL.S
void freeList(List* pQ){
   if(pQ!=NULL && *pQ!=NULL) { 
      while( !isEmpty(*pQ) ) { 
         deleteFront(*pQ); 
      }
      free(*pQ);
      *pQ = NULL;
   }
}


// Access functions -----------------------------------------------------------
int contains(List L, void* data){ // unnecessary. don't worry about this.
   Node theMatch = L->front;
   while(theMatch!=NULL){
     // printf("Lfront %d, theMatch %d\n", L->front, *theMatch);
     // printf("index %d\n", theMatch->index);
      if((theMatch->index)==(data)){//do i need to add *'s in front of index and data.
         return (1);
      }
      else{
         theMatch = theMatch->next;
      }
   }
   return 0;
}
// getFront()
// Returns the value at the front of Q.
// Pre: !isEmpty(Q)
void* front(List Q){
   if( Q==NULL ){
      printf("Queue Error: calling front() on NULL Queue reference\n");
      exit(1);
   }
   if( isEmpty(Q) ){
      printf("Queue Error: calling front() on an empty Queue\n");
      exit(1);
   }
   return(Q->front->index);
}
// back()
// Returns the value at the back of Q.
// Pre: !isEmpty(Q)
void* back(List Q){
   if( Q==NULL ){
      printf("Queue Error: calling front() on NULL Queue reference\n");
      exit(1);
   }
   if( isEmpty(Q) ){
      printf("Queue Error: calling front() on an empty Queue\n");
      exit(1);
   }
   return(Q->back->index);
}
// getLength()
// Returns the length of Q.
int length(List Q){
   if( Q==NULL ){
      printf("List Error: calling length() on NULL Queue reference\n");
      exit(1);
   }
   return(Q->length);
}
int index(List Q){
   if( Q==NULL ) {
      printf("List Error: calling index() on NULL Queue reference\n");
      exit(1);
   }
   if( Q->front==NULL){
      return(-1);
   }
   int i=-1;
   Node N = NULL;
   //printf("pinche ponche pouwnch index");
   ///if(Q->cursor==NULL){printf("Cursor is:NULL\n");}
   for(N=Q->cursor; N!=NULL;N=N->prev){
      i++;
   }
   return (i);
}
// get()
// returns
void* get(List Q){
   if( Q==NULL ){
      printf("List Error: calling get() on NULL Queue reference\n");
      exit(1);
   }
   if((length(Q)>0) && (index(Q)>=0)){
      return (Q->cursor->index);
   }else{
      printf("List Error: calling get() on an empty Queue or undefined cursor\n");
      exit(1);
   }
   //printf(" fine.");
}
// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty(List Q){
   if( Q==NULL ){
      printf("Queue Error: calling isEmpty() on NULL Queue reference\n");
      exit(1);
   }
   return(Q->length==0);
}

// equals()
// returns true (1) if A is identical to B, false (0) otherwise
/*int equals(List A, List B){ //unnecessary in pa2 
   if( A==NULL ){
      printf("List Error: calling equals() on NULL Queue reference List A\n");
      exit(1);
   }
   if( B==NULL ){
      printf("List Error: calling equals() on NULL Queue reference List B\n");
      exit(1);
   }
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("Queue Error: calling equals() on NULL Queue reference\n");
      exit(1);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = (N->index == M->index);//Do I need to compare the 
      N = N->next;
      M = M->next;
   }
   return eq;
}*/
// Manipulation procedures ----------------------------------------------------

void clear(List L){
   if( L==NULL ){
      printf("List Error: calling clear() on NULL Queue reference\n");
      exit(1);
   }
   while( !isEmpty(L) ){ 
         deleteFront(L); 
   }
   L->cursor = NULL;
   L->front = NULL;
   L->back = NULL;
   L->length = 0;
}
void moveFront(List L){
   if( L==NULL ){
      printf("List Error: calling moveFront() on NULL Queue reference\n");
      exit(1);
   }
   L->cursor = L->front;
   //printf("wuz brakyn bruh");
}
void moveBack(List L){
   if( L==NULL ){
      printf("List Error: calling moveBack() on NULL Queue reference\n");
      exit(1);
   }
   L->cursor = L->back;
}
void movePrev(List L){
   if( L==NULL ){
      printf("List Error: calling movePrev() on NULL Queue reference\n");
      exit(1);
   }
   if(L->cursor == NULL){
      return;
   }else{
      L->cursor = L->cursor->prev;
   }
}
void moveNext(List L){
   if( L==NULL ){
      printf("List Error: calling moveNext() on NULL Queue reference\n");
      exit(1);
   }
   if(L->cursor == NULL){
      return;
   }else{
      L->cursor = L->cursor->next;
   }
   //printf("ey next puto");
}
void append(List Q, void* data){
   Node N = newNode(data);
   //printf("%d",data);
   if( Q==NULL ){
      printf("List Error: calling append() on NULL Queue reference\n");
      exit(1);
   }
   if( isEmpty(Q) ) { 
      Q->front = Q->back = N;
      //printf("right");
     // printf("%d\n", Q->front->index); 
   }else{ 
      Q->back->next = N;
      N->prev = Q->back;
      Q->back = N;
      //printf("wrongie");
     // printf("%d\n", Q->back->index); 
   }
   Q->length++;
}
// prepend()
// Places new data element at the end of Q
void prepend(List Q, void* data){
   Node N = newNode(data);

   if( Q==NULL ){
      printf("List Error: calling prepend() on NULL Queue reference\n");
      exit(1);
   }
   if( isEmpty(Q) ) { 
      Q->front = Q->back = N; 
   }else{ 
      //printf("rightie\n");
      Q->front->prev = N; 
      N->next = Q->front;
      Q->front = N; 
   }
   Q->length++;
}

// deleteFront()
// Deletes element at front of Q
// Pre: !isEmpty(Q)
void deleteFront(List Q){
// printf("cursor1:%d", Q->cursor->index);  

//printf("cursor2:%d", Q->cursor->index);
   if( Q==NULL ){
      printf("List Error: calling deleteFront() on NULL Queue reference\n");
      exit(1);
   }
   if( isEmpty(Q) ){
      printf("List Error: calling deleteFront() on an empty Queue\n");
      exit(1);
   }
   Node N = NULL;
   N = Q->front;
//printf("cursor3:%d", Q->cursor->index);
   int i=0;
   if (index(Q)==0){
      i = 1;
   } 
   if( length(Q)>1 ) { 
      Q->front = Q->front->next;
      Q->front->prev = NULL;
// printf("cursor4:%d", Q->cursor->index);
   }else{ 
      Q->front = Q->back = NULL; 
   }
   if(i==1){
      Q->cursor = NULL;
   }
   Q->length--;
//printf("cursor5:%d", Q->cursor->index);
   freeNode(&N);
//printf("cursor6:%d", Q->cursor->index);
   
}

// deleteBack()
// Deletes element at front of Q
// Pre: !isEmpty(Q)
void deleteBack(List Q){
   
   if( Q==NULL ){
      printf("Queue Error: calling deleteBack() on NULL Queue reference\n");
      exit(1);
   }
   if( isEmpty(Q) ){
      printf("Queue Error: calling deleteBack() on an empty Queue\n");
      exit(1);
   }
   Node N = NULL;
   N = Q->back;
   int i=0;  
   if((index(Q)+1)==(length(Q))){
      i=1;
   }
   if( length(Q)>1 ) { 
      Q->back = Q->back->prev; //do I need to set Q.back.next = NULL?
      Q->back->next = NULL;
   }else{ 
      Q->front = Q->back = NULL; 
   }
   if (i==1){
      Q->cursor = NULL;
   }
   Q->length--;
   freeNode(&N);
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in Q on a single line to output file.
/*void printList(FILE* out, List Q){
   if( Q==NULL ){
      printf("List Error: calling printList() on NULL Queue reference\n");
      exit(1);
   }
   //printf("Q->front: %d\n", Q->front->index);
   Node N = NULL;
   //int Qlen = length(Q);
   //char Qdata[2200]="";
   //printf("%s\n",Qdata);
   for(N = Q->front; N != NULL; N = N->next){
      Entry x = (Entry)N->index; // do i need to change to void*?
      //char str[100];
      fprintf(out, "(%d, $f) ",x->col,x->entry);
      * ignore me_v
      if(N->next!=NULL){
         sprintf(str, "%f ", *x);
         strcat(Qdata, str);
         
      }else{
         sprintf(str, "%f", *x);
         strcat(Qdata, str);
      } 
      * ignore me^
   }
   //printf("%s\n", Qdata);
   fprintf(out, "%s\n", Qdata);
}*/
/*List copyList(List L){// unnecessary in pa2
   if( L==NULL ){
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(1);
   }
   List C = newList();
   Node N = L->front;
   while(N!=NULL){
      append(C, N->index);
      N = N->next;
   }
   return(C);
}*/
void insertBefore(List Q, void* data){
   Node N = newNode(data);

   if( Q==NULL ){
      printf("Queue Error: calling insertBefore() on NULL List reference\n");
      freeNode(&N);
      exit(1);
   }
   if( isEmpty(Q) || index(Q)<0 ) { 
      printf("List Error: insertBefore() called on empty List or undefined cursor");
      freeNode(&N);
      exit(1); 
   }else if(Q->cursor == Q->front){
      freeNode(&N);
      prepend(Q, data);
      Q->length--;
   }else{ 
      N->next = Q->cursor;
      N->prev = Q->cursor->prev;
      Q->cursor->prev->next = N;
      Q->cursor->prev = N;
   }
   Q->length++;
}
void insertAfter(List Q, void* data){
   Node N = newNode(data);

   if( Q==NULL ){
      printf("Queue Error: calling insertBefore() on NULL Queue reference\n");
      freeNode(&N);
      exit(1);
   }
   if( isEmpty(Q) || index(Q)<0 ) { 
      printf("List Error: insertBefore() called on empty List or undefined cursor");
      freeNode(&N);
      exit(1); 
   }else if(Q->cursor == Q->back){
      freeNode(&N);
      append(Q, data);
      Q->length--;
   }else{ 
      N->next = Q->cursor->next;
      N->prev = Q->cursor;
      Q->cursor->next->prev = N;
      Q->cursor->next = N;
   }
   Q->length++;
}
void delete(List L){
   if( L==NULL ){
      printf("List Error: calling printList() on NULL Queue reference\n");
      exit(1);
   }
   if(L->cursor==L->front){//if the cursor is at the front
      deleteFront(L);
   }else if(L->cursor==L->back){//if the cursor is at the back
      deleteBack(L);
   }else if(length(L)>0 && index(L)>=0){//
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      L->length--;
      freeNode(&(L->cursor));
      L->cursor = NULL;
   }else{
      printf("List Error: delete() called on empty List or undefined cursor");
      exit(1);
   }
}


