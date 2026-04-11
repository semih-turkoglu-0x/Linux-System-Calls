CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

all : ex1a ex1b ex1c ex1d ex3a ex3b ex3c ex3d

ex1a : ex1a.o 
	cc $(CFLAGS) -o ex1a ex1a.o 

ex1b : ex1b.o
	cc $(CFLAGS) -o ex1b ex1b.o

ex1c : ex1c.o
	cc $(CFLAGS) -o ex1c ex1c.o

ex1d : ex1d.o
	cc $(CFLAGS) -o ex1d ex1d.o

ex3a : ex3a.o 
	cc $(CFLAGS) -o ex3a ex3a.o 

ex3b : ex3b.o
	cc $(CFLAGS) -o ex3b ex3b.o

ex3c : ex3c.o
	cc $(CFLAGS) -o ex3c ex3c.o

ex3d : ex3d.o utils.o
	cc $(CFLAGS) -o ex3d ex3d.o utils.o

utils.o : utils.c utils.h
	cc $(CFLAGS) -c utils.c

clean :
	rm -f *.o
	rm -f ex1a ex1b ex1c ex1d ex3a ex3b ex3c ex3d