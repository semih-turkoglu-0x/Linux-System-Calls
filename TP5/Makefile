CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

all : ex3A ex3B

ex3A : ex3A.o
	cc $(CFLAGS) -o ex3A ex3A.o

ex3B : ex3B.o utils.o
	cc $(CFLAGS) -o ex3B ex3B.o utils.o

utils.o : utils.c utils.h
	cc $(CFLAGS) -c utils.c

clean :
	rm -f *.o
	rm -f ex3A ex3B