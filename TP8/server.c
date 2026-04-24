#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "messages.h"
#include "utils.h"

#define MAX_PLAYERS 2
#define BACKLOG 5

typedef struct Player
{
  char pseudo[MAX_PSEUDO];
  int sockfd;
} Player;

/**** SIGNAL HANDLER ******/

volatile sig_atomic_t end = 0;

void endServerHandler(int sig)
{
  end = 1;
}

/****** FUNCTIONS ********/

/**
 * PRE:  serverPort: a valid port number
 * POST: on success, binds a socket to 0.0.0.0:serverPort and listens to it ;
 *       on failure, displays error cause and quits the program
 * RES: return socket file descriptor
 */
int initSocketServer(int serverPort)
{
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("socket");
    exit(1);
  }

  int option = 1;
  int ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));
  if (ret == -1) {
    perror("setsockopt");
    exit(1);
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));

  addr.sin_family = AF_INET;
  addr.sin_port = htons(serverPort);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  ret = bind (sockfd, (struct sockaddr *)&addr, sizeof(addr));
  if (ret == -1) {
    perror("bind");
    exit(1);
  }

  ret = listen(sockfd, BACKLOG);
  if(ret == -1) {
    perror("listen");
    exit(1);
  }

  return sockfd;
}

/**
 * PRE:  tabPlayers: array of nbPlayers players
 * POST: print pseudos of the players in tabPlayers
 */
void displayPlayers(Player *tabPlayers, int nbPlayers)
{
  printf("\nJoueurs inscrits : \n");
  for (int i = 0; i < nbPlayers; i++)
  {
    printf("  - %s inscrit\n", tabPlayers[i].pseudo);
  }
}

/**
 * PRE:  tabPlayers: array of nbPlayers players
 * POST: close socket filedescriptors connected to 
 *       the players in tabPlayers
 */
void closeSockets (Player *tabPlayers, int nbPlayers) 
{
  for (int i = 0; i < nbPlayers; i++)
    sclose(tabPlayers[i].sockfd);
}

/****** MAIN PROGRAM ********/

int main(int argc, char **argv)
{
  StructMessage msg;
  Player tabPlayers[MAX_PLAYERS];
  int nbPlayers = 0;

  ssigaction(SIGTERM, endServerHandler);
  ssigaction(SIGINT, endServerHandler);

  int sockfd = initSocketServer(SERVER_PORT);
  printf("Le serveur tourne sur le port : %i \n", SERVER_PORT);

  while (!end)
  {
    /* client trt */
    int newsockfd = accept(sockfd, NULL, NULL);
    if (end) break;
    checkNeg(newsockfd, "ERROR accept");

    ssize_t ret = read(newsockfd, &msg, sizeof(msg));
    if (end) break;
    checkCond(ret != sizeof(msg), "ERROR READ");

    printf("Inscription demandée par le joueur : %s\n", msg.messageText);
    if (nbPlayers < MAX_PLAYERS && strlen(msg.messageText) > 0)
    {
      msg.code = INSCRIPTION_OK;
      strcpy(tabPlayers[nbPlayers].pseudo, msg.messageText);
      tabPlayers[nbPlayers].sockfd = newsockfd;
      nbPlayers++;
    }
    else
    {
      msg.code = INSCRIPTION_KO;
    }

    nwrite(newsockfd, &msg, sizeof(msg));
    printf("Nb Inscriptions : %i\n", nbPlayers);
  }
  
  displayPlayers(tabPlayers, nbPlayers);
  closeSockets(tabPlayers, nbPlayers);  // fermeture des sockets connectés aux clients
  sclose(sockfd);   // fermeture du socket d'écoute
}
