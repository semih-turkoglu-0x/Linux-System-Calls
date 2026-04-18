CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

ALL = ex4_1a ex4_1b ex4_1c timer

all : $(ALL)

ex4_1a : ex4_1a.o utils.o
	cc $(CFLAGS) -o ex4_1a ex4_1a.o utils.o

ex4_1b : ex4_1b.o utils.o
	cc $(CFLAGS) -o ex4_1b ex4_1b.o utils.o

ex4_1c : ex4_1c.o utils.o
	cc $(CFLAGS) -o ex4_1c ex4_1c.o utils.o

timer : ex4_2.o utils.o
	cc $(CFLAGS) -o timer ex4_2.o utils.o

ex4_3 : ex4_3.o
	cc $(CFLAGS) -o ex4_3 ex4_3.o

utils : utils.c utils.h
	cc $(CFLAGS) -o utils.o

clean : 
	rm -f *.o
	rm -f $(ALL)