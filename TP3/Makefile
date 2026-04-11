CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

all : lire ex2

lire : lire.o utils.o
	cc $(CFLAGS) -o lire lire.o utils.o

ex2 : ex2.o utils.o
	cc $(CFLAGS) -o ex2 ex2.o utils.o

utils.o : utils.c utils.h
	cc $(CFLAGS) -c utils.c

clean :
	rm -f *.o
	rm -f lire ex2