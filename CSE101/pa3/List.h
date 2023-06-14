//Pablo Gomez-Echegaray
//pgomezec
//pa1
#ifndef _LIST_H_INCLUDE_ 
#define _LIST_H_INCLUDE_ 

// Constructors-Destructors ---------------------------------------------------
// private NodeObj type
typedef struct NodeObj{
   long index;
   struct NodeObj* next;
   struct NodeObj* prev;
   //char line[1000];
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
int index(List L);//
long front(List L);//
long back(List L);//
long get(List L);//
int equalsList(List A, List B);//
int isEmpty(List L);
int contains(List L, long data);
// Manipulation procedures 
//----------------------------------------------------
void clear(List L);//
void moveFront(List L);//
void moveBack(List L);//
void movePrev(List L);//
void moveNext(List L);//
void prepend(List L, long data);//
void append(List L, long data);//
void insertBefore(List L, long data);//
void insertAfter(List L, long data);//
void deleteFront(List L);//
void deleteBack(List L);//
void delete(List L);//
void set(List L, long x);
// Other operations 
//-----------------------------------------------------------
void printList(FILE* out, List L);//
List copyList(List L);

#endif
