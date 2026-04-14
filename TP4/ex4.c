#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "utils.h"

#define MAX_FILE 20
#define MAX_LINE 50

void clearStdin() {
    char bufLeft[MAX_LINE];
    int nbCharLeft = read(0, bufLeft, MAX_LINE);
    while (nbCharLeft > 0 && bufLeft[nbCharLeft-1] != '\n') {
        read(0, bufLeft, MAX_LINE);
    }
    printf("stdin was emptied\n");
}

int main (int argc, char** argv) {
    printf("saisissez le nom du fichier :\n");
    char bufRd[MAX_FILE];
    int nbChar = sread(0, bufRd, MAX_FILE);
    //putting \0 at the end of the string so that the program recognizes it
    bufRd[nbChar - 1] = '\0';
    int fd = sopen(bufRd, O_RDWR |  O_CREAT | O_TRUNC, 0744);

    //create the first childProcess that will execute the ls -l command
    int child1Pid = fork();
    int child1Status;

    if (child1Pid == -1) {
        perror("fork error\n");
        exit(EXIT_FAILURE);
    }

    if (!child1Pid) {
        close (fd);
        char* args[] = {"ls", "-l", NULL};
        execv("/bin/ls", args);
        perror("error execv\n");
        exit(EXIT_FAILURE);
        } else {
            //waiting for the child to execute ls -l
            waitpid(child1Pid, &child1Status, 0);
            //write the shebang in the newly created script
            char* shBg = "#!/bin/bash\n";
            write(fd, shBg, strlen(shBg));

            printf("enter the lines of your script. Ctrl-D to finish.\n");

            char bufScript[MAX_LINE];
            int nbCharScript = read(0, bufScript, MAX_LINE);
            while (nbCharScript > 0) {
                if (bufScript[nbCharScript-1] == '\n') {
                    write(fd, bufScript, strlen(bufScript));
                } else {
                    perror("error : line is too big");
                    clearStdin();
                    exit(EXIT_FAILURE);
                }
                nbCharScript = read(0, bufScript, MAX_LINE);
            }
            exit(EXIT_SUCCESS);
    }
}
