CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

ALL = ex4_1a ex4_1b ex4_1c

all : $(ALL)

ex4_1a : ex4_1a.o utils.o
	cc $(CFLAGS) -o ex4_1a ex4_1a.o utils.o

ex4_1b : ex4_1b.o utils.o
	cc $(CFLAGS) -o ex4_1b ex4_1b.o utils.o

ex4_1c : ex4_1c.o utils.o
	cc $(CFLAGS) -o ex4_1c ex4_1c.o utils.o

utils : utils.c utils.h
	cc $(CFLAGS) -o utils.o

clean : 
	rm -f *.o
	rm -f $(ALL)