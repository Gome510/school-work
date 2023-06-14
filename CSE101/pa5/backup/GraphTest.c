
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

int main(void){/*
    printf("Hello World");
        Graph G = newGraph(5);
    addEdge(G,1,2);
    addEdge(G,1,3);
    addEdge(G,2,4);
    addEdge(G,3,5);

    printGraph(stdout,G);
    
    makeNull(G);
    freeGraph(&G);
*//*
    Graph A = newGraph(100);
    addArc(A, 54, 1);
    printf("getSize(A)=%d",getSize(A));
    addArc(A, 54, 2);
    printf("getSize(A)=%d",getSize(A));
    addArc(A, 54, 3);
    printf("getSize(A)=%d",getSize(A));
    addArc(A, 1, 54);
    printf("getSize(A)=%d",getSize(A));
    addArc(A, 1, 55);
    printf("getSize(A)=%d",getSize(A));
    makeNull(A);
    freeGraph(&A);
*/
    Graph A = newGraph(100);
    List L = newList();
    List C = newList();
    
        addArc(A, 64, 4);
        addArc(A, 64, 3);
        addArc(A, 42, 2);
        addArc(A, 2, 64);
        addArc(A, 4, 2);
        addArc(A, 3, 42);
        BFS(A, 3);
        getPath(L, A, 64);
        append(C, 3);
        append(C, 42);
        append(C, 2);
        append(C, 64);
        printList(stdout,L);
        printList(stdout,C);
        moveFront(L);
        BFS(A, 2);
        getPath(L, A, 2);
        append(C, 2);
                printList(stdout,L);
        printList(stdout,C);
        
        clear(L);
        clear(C);
        freeList(&L);
        freeList(&C);
            makeNull(A);
    freeGraph(&A);
}
