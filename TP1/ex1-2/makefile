CFLAGS=-std=c17 -pedantic -Wvla -Werror -Wall -D_DEFAULT_SOURCE -g

all : encryptROT13 decryptROT13

encryptROT13 : encryptROT13.o cryptROT13.o utils.o
	cc $(CFLAGS) -o encryptROT13 encryptROT13.o cryptROT13.o utils.o

decryptROT13 :  cryptROT13.o decryptROT13.o utils.o
	cc $(CFLAGS) -o decryptROT13 decryptROT13.o cryptROT13.o utils.o

cryptROT13.o : cryptROT13.c cryptROT13.h
	cc $(CFLAGS) -c cryptROT13.c

encryptROT13.o : encryptROT13.c cryptROT13.h utils.h
	cc $(CFLAGS) -c encryptROT13.c

decryptROT13.o : decryptROT13.c cryptROT13.h utils.h
	cc $(CLAGS) -c decryptROT13.c

utils.o : utils.c utils.h
	cc $(CFLAGS) -c utils.c

clean :
	rm -f *.o
	rm -f encryptROT13 decryptROT13