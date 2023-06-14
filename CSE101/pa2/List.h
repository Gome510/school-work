//Pablo Gomez-Echegaray
//pgomezec
//pa2
#ifndef _LIST_H_INCLUDE_ 
#define _LIST_H_INCLUDE_ 

// Constructors-Destructors ---------------------------------------------------
// private NodeObj type
typedef struct NodeObj{
   void* index;
   struct NodeObj* next;
   struct NodeObj* prev;
   char line[1000];
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
void* front(List L);//--
void* back(List L);//--
void* get(List L);//--
//int equals(List A, List B);//--
int isEmpty(List L);
int contains(List L, void* data);//--
// Manipulation procedures 
//----------------------------------------------------
void clear(List L);//
void moveFront(List L);//
void moveBack(List L);//
void movePrev(List L);//
void moveNext(List L);//
void prepend(List L, void* data);//
void append(List L, void* data);//
void insertBefore(List L, void* data);//
void insertAfter(List L, void* data);//
void deleteFront(List L);//
void deleteBack(List L);//
void delete(List L);//
// Other operations 
//-----------------------------------------------------------
//void printList(FILE* out, List L);//
//List copyList(List L);

#endif
