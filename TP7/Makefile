CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

ALL = radar dashboard famille1 famille2 locks
all : $(ALL)

radar : radar.o utils.o
	cc $(CFLAGS) -o radar radar.o utils.o

dashboard : dashboard.o utils.o
	cc $(CFLAGS) -o dashboard dashboard.o utils.o

famille1 : famille1.o utils.o
	cc $(CFLAGS) -o famille1 famille1.o utils.o

famille2 : famille2.o utils.o
	cc $(CFLAGS) -o famille2 famille2.o utils.o

locks : locks.o utils.o
	cc $(CFLAGS) -o locks locks.o utils.o

utils : utils.c utils.h
	cc $(CFLAGS) -o utils.o

clean :
	rm -f *.o
	rm -f $(ALL)