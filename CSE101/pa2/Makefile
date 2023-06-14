#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 2
#  pgomezec
#  Pablo Gomez-Echegaray
#
#  make                     makes MatrixClient
#  make clean               removes all binaries
#  make memcheck            runs Matrix Client under valgrind
#------------------------------------------------------------------------------

CLIENT         = MatrixClient
SPARSE	       = Sparse
ADT1           = Matrix
ADT2           = List
SSOURCE        = $(SPARSE).c
SOBJECT        = $(SPARSE).o
SOURCE         = $(CLIENT).c
OBJECT         = $(CLIENT).o
ADT1_SOURCE    = $(ADT1).c
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT2_SOURCE    = $(ADT2).c
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
COMPILE        = gcc -c -std=c99 -Wall -g
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(SPARSE) : $(SOBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(SPARSE) $(SOBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	
$(CLIENT) : $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(OBJECT) : $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_OBJECT) : $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT) : $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(SPARSE) $(SOBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT)


