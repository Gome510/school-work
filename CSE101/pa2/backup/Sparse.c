//Pablo Gomez-Echegaray
//pa2
//pgomezec

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Matrix.h"
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




//-----------------------------------------------------------------------------
    fclose(in);
    fclose(out);
}