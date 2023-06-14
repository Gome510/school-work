//Pablo Gomez-Echegaray
//pgomezec
//pa5
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#define INF -1
#define NIL 0
//Graph ADT
typedef struct GraphObj{
    List *adjList;
    int order;
    int size;
    int vert;
    int *color;
    int *parent;
    int *dist;
    int *start;
    int *finish;
} GraphObj;
typedef GraphObj* Graph;
/*** Constructors-Destructors ***/
Graph newGraph(int n){
    Graph G = (malloc(sizeof(GraphObj)));
    G->adjList = (malloc(sizeof(List)*(n+1)));
    G->color = (malloc(sizeof(int)*(n+1)));
    G->parent = (malloc(sizeof(int)*(n+1)));
    G->dist = (malloc(sizeof(int)*(n+1)));
    G->start = (malloc(sizeof(int)*(n+1)));
    G->finish = (malloc(sizeof(int)*(n+1)));
    G->order =n;
    G->size = 0;
    G->vert = NIL;
    
    /*int color[n+1];
    G->color = color;
    
    int parent[n+1];
    G->parent = parent;
    
    int dist[n+1];
    G->dist = dist;*/
    G->adjList[0] = NULL;
    for(int i = 0; i<=n;i++){
        G->adjList[i] = newList();
        G->parent[i] = NIL;
        G->color[i] = 0;
        G->dist[i] = INF;
        G->start[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    return G;
}

void freeGraph(Graph* pG){
/*    free(&pG->adjList);
    free(&pG->color);
    free(&pG->parent);
    free(&pG->dist);
    free(&pG->order);
    free(*pG->size);
    free(*pG->vert);
    for(int i =0; i<getSize(*pG)+1;i++){
        freeList(&((*pG) -> adjList[i]));
    }*/
    int n = (*pG)->order;
    //printf("%d\n",n);
    for(int i = 0; i<=n;i++){
        //printf("Freeing G->adjList[%d]\n",i);
        freeList(&((*pG)->adjList[i]));
    }
    free((*pG)->adjList);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->dist);
	free((*pG)->start);
	free((*pG)->finish);
    (*pG)->adjList=NULL;
    (*pG)->color=NULL;
    (*pG)->parent=NULL;
    (*pG)->dist=NULL;
	(*pG)->start=NULL;
	(*pG)->finish=NULL;
    free(*pG);
    *pG = NULL;
}
/*** Access functions ***/
int getOrder(Graph G){
    if(G==NULL){
        printf("Graph Error: getOrder(Graph G) called where G==NULL");
        exit(1);
    }else{
        return G->order;
    }
}
int getSize(Graph G){
    return G->size;
}
//getSource() returns the source vertex most recently used in function BFS(), or NIL if
//  BFS() has not yet been called. 
int getSource(Graph G){
    return G->vert;
}
//Function getParent() will return the parent of vertex u in the 
//  BreadthFirst tree created by BFS(), or NIL if BFS() has not yet been called. 
int getParent(Graph G, int u){
    return G->parent[u];
}
//Function getDist() returns the distance from the most recent BFS source
//  to vertex u, or INF if BFS() has not yet been called.
int getDist(Graph G, int u){
    return G->dist[u];
}
int getDiscover(Graph G, int u){ /* Pre: 1<=u<=n=getOrder(G) */
    if(1<=u && u<=getOrder(G)){
		return G->start[u];
	}else{
		printf("Graph Error: called getDiscover() when u is not in the range 1<=u<=n=getOrder(G)");
		exit(1);
	}
}
int getFinish(Graph G, int u){ /* Pre: 1<=u<=n=getOrder(G) */
    if(1<=u && u<=getOrder(G)){
		return G->finish[u];
	}else{
		printf("Graph Error: called getFinish() when u is not in the range 1<=u<=n=getOrder(G)");
		exit(1);
	}
}
//getPath() appends to the List L the vertices of a shortest path in G from source to u, or 
//  appends to L the value NIL if no such path exists.
void getPath(List L, Graph G, int u){
    if(getSource(G)!=NIL){
        if((1<=u)&& (u<=getOrder(G))){
			/*if(u==getSource(G)){
				prepend(L,u);
			}else if(G->parent[u]==NIL){
				append(L,NIL);
			}else{
				getPath(L,G,G->parent[u]);
			}*/
			
            int d = u;
            prepend(L,d);
            while(G->parent[d]!=NIL){
                prepend(L, G->parent[d]);
                d = G->parent[d];
            }
            if((front(L))!=(getSource(G))){
                append(L, NIL);
            }
        }else{
            printf("Graph Error: getPath was called when u<1 or u>getOrder()");
            exit(1);
        }
    }else{
        printf("Graph Error: getPath was called when getSource(G)= NIL.\n");
        exit(1);
    }
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
    int N = getOrder(G);
    for(int i = 1; i<=N; i++){
        clear(G->adjList[i]);
		G->parent[i] = 0;
		G->dist[i] = 0;
		G->color[i] = 0;
		G->start[i] = UNDEF;
		G->finish[i] = UNDEF;
    }
    G->vert=NIL;
    G->size=0;
}
void addEdge(Graph G, int u, int v){//undirected edge. vertices are added to each other's adjacency lists.
    //printf("%d %d\n", u, v);
    int N = getOrder(G);
    int b = 1;
    if(((1<=u)&&(u<=N))&&((1<=v)&&(v<=N))){
        List U = G->adjList[u];
        List V = G->adjList[v];
        if(U==NULL){
            //printf("U==Null\n");
        }
        if(V==NULL){
            //printf("V==Null\n");
        }
        moveFront(U);
        moveFront(V);
        if(U->cursor==NULL){
            //printf("U->cursor==NULL\n");
            append(U, v);
        }
        while(U->cursor!=NULL){//
            if(get(U)==v){//if the adjacent vertex is already known
                //printf("get(U)==v\n");
                b--;//we're not adding an edge in this case so we don't increase the size.
                break;
            }else if(get(U)>v){
                //printf("get(U)>v\n");
                insertBefore(U,v);
                break;
            }
            moveNext(U);
            if(U->cursor==NULL){
                //printf("U->cursor==NULL\n");
                append(U, v);
                break;
            }
        }
        if(V->cursor==NULL){
            //printf("V->cursor==NULL\n");
            append(V, u);
        }
        while(V->cursor!=NULL){
            if(get(V)==u){//if the adjacent vertex is already known
                //printf("get(V)==u\n");
                b--;
                break;
            }else if(get(V)>u){
                //printf("get(V)>u\n");
                insertBefore(V,u);
                break;
                
            }
            moveNext(V);
            if(V->cursor==NULL){
                //printf("V->cursor==NULL\n");
                append(V, u);
                break;
            }
        }
        if(b==1){
            G->size++;
        }
        G->adjList[u] = U;
        G->adjList[v] = V;
    }else{
        printf("Graph Error: addEdge() was called with u or v out of range [1, getSize(G)].\n");
        exit(1);
    }
}
void addArc(Graph G, int u, int v){
    int N = getOrder(G);
    int b = 1;
    if(((1<=u)&&(u<=N))&&((1<=v)&&(v<=N))){
        List U = G->adjList[u];
        if(U==NULL){
            //printf("U==Null\n");
        }
        moveFront(U);
        if(U->cursor==NULL){
            //printf("U->cursor==NULL\n");
            append(U, v);
        }
        while(U->cursor!=NULL){//
            if(get(U)==v){//if the adjacent vertex is already known.
                //printf("get(U)==v\n");
                b--;//we're not adding an edge in this case so we don't increase the size.
                break;
            }else if(get(U)>v){// if v belongs in between vertices or at the beginning.
                //printf("get(U)>v\n");
                insertBefore(U,v);
                break;
            }
            moveNext(U);
            if(U->cursor==NULL){//if v belongs at the end of the list.
                //printf("U->cursor==NULL\n");
                append(U, v);
                break;
            }
        }
        if(b==1){
            G->size++;
        }
        G->adjList[u] = U;
        
    }else{
        printf("Graph Error: addArc() was called with u or v out of range [1, getOrder(G)].\n");
        exit(1);
    }
}
void BFS(Graph G, int s){
    G->vert = s;
    List Q = newList();
    prepend(Q,s);//Enqueue(Q,s)
    int N = getOrder(G);
    for(int i = 1; i<=N; i++){
        G->parent[i] = NIL;
        G->color[i] = 0;
        G->dist[i] = INF;
    }
    G->color[s]++;
    G->dist[s] = 0;
    
    while(!isEmpty(Q)){
        int u = front(Q);
        deleteFront(Q);//Dequeue(Q)
        //List U = G->adjList[u];
        moveFront(G->adjList[u]);
        while(G->adjList[u]->cursor!=NULL){//for each vertex, v, that is adjacent to u
            int v = get(G->adjList[u]);
            if(G->color[v]==0){
                G->color[v]=1;
                G->dist[v]=(G->dist[u])+1;
                G->parent[v]=u;
                append(Q,v);//Enqueue(Q,v)
            }
            
            moveNext(G->adjList[u]);
        }
        G->color[u]=2;
    }
    freeList(&Q);
}
void DFS(Graph G, List S){ /* Pre: length(S)==getOrder(G) */
	if(length(S)==getOrder(G)){
        List Q = copyList(S);
        clear(S);
		int time = 0;
		//for(int i =1; i<=getOrder(G); i++){
		moveFront(Q);
		while(Q->cursor!=NULL){
			G->color[get(Q)]= 0;
			G->parent[get(Q)]= NIL;
			moveNext(Q);
		}
		moveFront(Q);
		//for(int i =1; i<=getOrder(G); i++){
		while(Q->cursor!=NULL){
			if(G->color[get(Q)]==0){
				time = Visit(G,S,get(Q),time);
			}
			moveNext(Q);
			deleteFront(Q);
		}
        clear(Q);
        freeList(&Q);
        
	}else{
		printf("Graph Error: called DFS() while length(S)!=getOrder(G)");
		exit(1);
	}
}
int Visit(Graph G, List S, int u, int time){
	G->start[u] = ++time;
	G->color[u] = 1;
	moveFront(G->adjList[u]);
	while(G->adjList[u]->cursor!=NULL){
		if(G->color[get(G->adjList[u])] == 0){
			G->parent[get(G->adjList[u])] = u;
			time = Visit(G,S, get(G->adjList[u]),time);
		}
        moveNext(G->adjList[u]);
	}
	G->color[u] = 2;
	G->finish[u] = ++time;
    prepend(S,u);
    return time;
}

/*** Other operations ***/
Graph transpose(Graph G){
	if(G==NULL){
		printf("Graph Error: called transpose() while Graph G == NULL\n");
		exit(1);
	}else{
		Graph T = newGraph(getOrder(G));
		for(int i =1;i<=getOrder(G);i++){
			moveFront(G->adjList[i]);
			while(G->adjList[i]->cursor!=NULL){
				addArc(T,get(G->adjList[i]), i);
				moveNext(G->adjList[i]);
			}
		}
		return T;
	}
}
Graph copyGraph(Graph G){
	if(G==NULL){
		printf("Graph Error: called copyGraph() while Graph G == NULL\n");
		exit(1);
	}else{
		Graph T = newGraph(getOrder(G));
		for(int i =1;i<=getOrder(G);i++){
			moveFront(G->adjList[i]);
			while(G->adjList[i]->cursor!=NULL){
				addArc(T,i, get(G->adjList[i]));
				T->color[i]= G->color[i];
				T->start[i]= G->start[i];
				T->finish[i]= G->finish[i];
				T->parent[i]= G->parent[i];
				moveNext(G->adjList[i]);
			}
		}
		return T;
	}
}
void printGraph(FILE* out, Graph G){
    fprintf(out,"Adjacency list representation of G:\n");
    int N = getOrder(G);
    for(int i =1; i<=N;i++){
        List L = G->adjList[i];
        //printf("A");
        fprintf(out,"%d:",i);
        //printf("%d: ",i);
        moveFront(L);
        //printf("B");
        while(L->cursor!=NULL){
            //printf("yes");
            fprintf(out," %d",get(L));
           // printf("%d ",get(L));
            moveNext(L);
        }
        fprintf(out,"\n");
    }
}
void printSCC(FILE* out, Graph T, List S){
    moveFront(S);
    int n=0;
    while(S->cursor!=NULL){
        if(T->parent[get(S)]==NIL){
            n++;
        }
        moveNext(S);
    }
    fprintf(out, "\nG contains %d strongly connected components:", n);
    Node P;
    moveBack(S);
    int i = 0;
    while(S->cursor!=NULL){
        if(T->parent[get(S)]==NIL){
            P = S->cursor;
            fprintf(out, "\nComponent %d:",++i);
            while(S->cursor!=NULL){
                
                int d = get(S);
                fprintf(out," %d", d);
                moveNext(S);
                if(S->cursor == NULL){
                    break;
                }
                if(T->parent[get(S)]==NIL){
                    break;
                }
            }
            S->cursor = P;
        }
        movePrev(S);
    }
    fprintf(out,"\n");
}
