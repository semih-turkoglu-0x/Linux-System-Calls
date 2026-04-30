CC=gcc

CCFLAGS=-std=c17 -pedantic -Wall -Wvla -Werror -Wno-unused-variable -D_DEFAULT_SOURCE

ALL= server client crawler

all: $(ALL)

server : server.o utils.o
	$(CC) $(CCFLAGS) -o server server.o utils.o

server.o: server.c messages.h utils.h
	$(CC) $(CCFLAGS) -c server.c

client : client.o utils.o
	$(CC) $(CCFLAGS) -o client client.o utils.o

client.o: client.c messages.h utils.h
	$(CC) $(CCFLAGS) -c client.c

crawler : crawler.o utils.o
	$(CC) $(CCFLAGS) -o crawler crawler.o utils.o

crawler.o : crawler.c utils.h
	$(CC) $(CCFLAGS) -c crawler.c

utils.o: utils.c utils.h
	$(CC) $(CCFLAGS) -c utils.c

clean:
	rm -f *.o
	rm -f $(ALL)		