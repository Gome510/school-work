//Pablo Gomez-Echegaray
//pgomezec
//pa5
#define INF -1
#define NIL 0
#define UNDEF 0

#ifndef _GRAPH_H_INCLUDE_ 
#define _GRAPH_H_INCLUDE_ 
#include "List.h"

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */
int Visit(Graph G, List S, int u, int time);
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
void printSCC(FILE* out, Graph T, List S);
#endif
