#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "utils.h"

#define SERVER_PORT 80
#define BUFFER_SIZE 4096

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

  int ret = inet_aton(serverIP, &addr.sin_addr);
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

int main () {
    //open sitemap.txt and read it via readFileToTable
    int file_fd = sopen("./sitemap.txt", O_RDWR, 0666);

    char** websites = readFileToTable(file_fd);
    if (websites == NULL) {
      perror("readfiletotable");
      exit(1);
    }

    char ip[INET6_ADDRSTRLEN];
    bool ok = hostname_to_ip("courslinux.vinci.be", ip);
    if (!ok) {
      perror("impossible de resoudre le hostname");
      exit(1);
    }
    printf("IP du serveur : %s\n", ip);

    int i = 0;
    while (websites[i] != NULL) {
      char pageName[128];
      sprintf(pageName, "%s", strrchr(websites[i], '/')+1);

      int sockfd = initSocketClient(ip, SERVER_PORT);

      char request[256];
      sprintf(request, "GET %s HTTP/1.0\r\nHost: courslinux.vinci.be\r\n\r\n", websites[i]);

      swrite(sockfd, request, strlen(request));

      int fd = open(pageName, O_RDWR | O_CREAT | O_TRUNC, 0666);
      if (fd == -1) {
        perror("error creating file");
        exit(1);
      }

      char buffer[BUFFER_SIZE];
      int nbRead;
      while((nbRead = read(sockfd, buffer, BUFFER_SIZE)) > 0) {
        swrite(fd, buffer, nbRead);
      }

      close(fd);
      close(sockfd);

      i++;
    }

    return 0;
    
}