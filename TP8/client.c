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

/****** FUNCTIONS ********/

/**
 * PRE: serverIP: a valid IP address
 *      serverPort: a valid port number
 * POST: on success, connects a client socket to serverIP:serverPort
 *       on failure, displays error cause and quits the program
 * RES: return socket file descriptor
 */
int initSocketClient(char * serverIP, int serverPort)
{
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("socket");
    exit(1);
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  

  addr.sin_family = AF_INET;

  addr.sin_port = htons(SERVER_PORT);

  int ret = inet_aton(SERVER_IP, &addr.sin_addr);
  if (ret == 0) {
    perror("inet_aton");
    exit(1);
  }

  ret = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
  if (ret == -1) {
    perror("connect");
    exit(1);
  }
  return sockfd;
}

/****** MAIN PROGRAM ********/

int main(int argc, char **argv)
{
  /* retrieve player name */
  printf("Bienvenue dans le programe d'inscription au serveur de jeu\n");
  printf("Pour participer entrez votre nom :\n");
  StructMessage msg;
  int ret = sread(0, msg.messageText, MAX_PSEUDO);
  if (ret < 2) {
    printf("Erreur: vous devez entrer un nom de joueur\n");
    exit(1);
  }
  msg.messageText[ret - 1] = '\0';
  msg.code = INSCRIPTION_REQUEST;

  int sockfd = initSocketClient(SERVER_IP, SERVER_PORT);
  swrite(sockfd, &msg, sizeof(msg));

  /* wait server response */
  sread(sockfd, &msg, sizeof(msg));

  if (msg.code == INSCRIPTION_OK)
  {
    printf("Réponse du serveur : Inscription acceptée\n");
  }
  else if (msg.code == INSCRIPTION_KO)
  {
    printf("Réponse du serveur : Inscription refusée\n");
  }

  sclose(sockfd);
}
