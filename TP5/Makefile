CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

ALL= ex3A ex3B ex3C pipe createInscriptionRequests pgmInscription pgmInscriptionBis
all : $(ALL)

ex3A : ex3A.o
	cc $(CFLAGS) -o ex3A ex3A.o

ex3B : ex3B.o utils.o
	cc $(CFLAGS) -o ex3B ex3B.o utils.o

ex3C : ex3C.o
	cc $(CFLAGS) -o ex3C ex3C.o

pipe : pipe.o utils.o
	cc $(CFLAGS) -o pipe pipe.o utils.o

createInscriptionRequests : createInscriptionRequests.o
	cc $(CFLAGS) -o createInscriptionRequests createInscriptionRequests.o

pgmInscription : pgmInscription.o utils.o
	cc $(CFLAGS) -o pgmInscription pgmInscription.o utils.o

pgmInscriptionBis : pgmInscriptionBis.o utils.o
	cc $(CFLAGS) -o pgmInscriptionBis pgmInscriptionBis.o utils.o

utils.o : utils.c utils.h
	cc $(CFLAGS) -c utils.c

clean :
	rm -f *.o
	rm -f $(ALL)
	rm -f DemandesInscriptions.bin