//Pablo Gomez-Echegaray
//pa4
//pgomezec

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Graph.h"
//#include "List.h"

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
//-----------------------------------------------------------------------------
    //List A = newList();//my pseudo-arraylist
    //int n = 0;
    char str[50];
    char zz[50] = "0 0";
    char *cU, *cV;
    
    fgets(str, 50, in);//put the string of the first number into first. 
    //char* str1 = strtok(first," ");
    int part1 = atoi(str);//convert to int.
    
    
    Graph G = newGraph(part1);
    while(fgets(str, 50, in)!=zz){//while in.hasNextLine store 50 characters of the line into str.
        //put the whole line in str.
        
        cU = strtok(str," ");//put the string version of u in str
        int u = atoi(cU);//convert u to int
        
        cV = strtok(NULL," ");//get the next token from str.
        int v = atoi(cV);//convert this token to int.
        if(u==0 && v==0){//when you hit "0 0", move on.
            break;
        }
        addEdge(G,u,v);
    }//form the Graph Adjacency Lists
    printGraph(out, G);
    //fgets(str, 50, in);
    
    if (str==zz){
        //printf("Part 1 - ends, Part 2 - begins");
    }
    //fprintf(out,"\n");
    List L = newList();
    while(fgets(str, 50, in)!=zz){//while in.hasNextLine store 50 characters of the line into str.
        //put the whole line in str.
        
        cU = strtok(str," ");//put the string version of u in str
        int u = atoi(cU);//convert u to int
        
        cV = strtok(NULL," ");//get the next token from str.
        int v = atoi(cV);//convert this token to int.
        if(u==0 && v==0){//when you hit "0 0", move on.
            break;
        }
        BFS(G,u);
        getPath(L,G,v);
        if(back(L)==NIL){
            
            fprintf(out,"\n");
            fprintf(out,"The distance from %d to %d is infinity\n",u,v);
            fprintf(out,"No %d-%d path exists",u,v);
            
        }else{
            fprintf(out,"\n");
            fprintf(out,"The distance from %d to %d is %d\n",u,v,getDist(G,v));
            moveFront(L);
            fprintf(out,"A shortest %d-%d path is:",u,v);
            while(L->cursor!=NULL){
                fprintf(out," %d",get(L));
                moveNext(L);
            }
            fprintf(out,"\n");
        }
        clear(L);
    }
    clear(L);
    freeList(&L);
    makeNull(G);
    freeGraph(&G);
    fclose(in);
    fclose(out);


}
