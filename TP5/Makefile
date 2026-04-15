CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

all : ex3A

ex3A : ex3A.o
	cc $(CFLAGS) -o ex3A ex3A.o

clean :
	rm -f *.o
	rm -f ex3A