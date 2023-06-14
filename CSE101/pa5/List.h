//Pablo Gomez-Echegaray
//pgomezec
//pa5
#ifndef _LIST_H_INCLUDE_ 
#define _LIST_H_INCLUDE_ 

// Constructors-Destructors ---------------------------------------------------
// private NodeObj type
typedef struct NodeObj{
   int index;
   struct NodeObj* next;
   struct NodeObj* prev;
   char line[50];
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private QueueObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
} ListObj;
typedef struct ListObj* List;
List newList(void);
void freeList(List* pL);//
// Access functions 
//-----------------------------------------------------------
int length(List L);//
int index(List L);//need for hash table
int front(List L);//
int back(List L);//need for hash table
int get(List L);//need for hash table
int equals(List A, List B);//
int isEmpty(List L);
int contains(List L, int data);//need for hash table
// Manipulation procedures 
//----------------------------------------------------
void clear(List L);//need for hash table
void moveFront(List L);//
void moveBack(List L);//need for hash table
void movePrev(List L);//
void moveNext(List L);//
void prepend(List L, int data);//
void append(List L, int data);//need for hash table
void insertBefore(List L, int data);//
void insertAfter(List L, int data);//
void deleteFront(List L);//
void deleteBack(List L);//
void delete(List L);//
// Other operations 
//-----------------------------------------------------------
void printList(FILE* out, List L);//need for hash table
List copyList(List L);

#endif
