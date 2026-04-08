CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

all : lire

lire : lire.o utils.o
	cc $(CFLAGS) -o lire lire.o utils.o

utils.o : utils.c utils.h
	cc $(CFLAGS) -c utils.c

clean :
	rm -f *.o
	rm -f lire