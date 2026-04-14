#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "utils.h"

#define MAX 20

int main (int argc, char** argv) {
    printf("saisissez le nom du fichier :\n");
    char bufRd[MAX];
    int nbChar = sread(0, bufRd, MAX);
    bufRd[nbChar - 1] = '\0';
    sopen(bufRd, O_RDWR |  O_CREAT | O_TRUNC, 0744);

    int childPid = fork();
    int childStatus;

    if (childPid == -1) {
        perror("fork error\n");
        exit(EXIT_FAILURE);
    }

    if (!childPid) {
        char* args[] = {"ls", "-l", NULL};
        execv("/bin/ls", args);
        perror("error execv\n");
        exit(EXIT_FAILURE);
        } else {
        waitpid(childPid, &childStatus, 0);
        exit(EXIT_SUCCESS); 
    }
}
