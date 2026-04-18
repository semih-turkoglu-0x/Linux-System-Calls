#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_LINE 80

static const char *const MSG = "---> SIGPIPE Recu par le pere: \nimpossible de transmettre les donnees sur le pipe\n";

void sigHandler(int sig) {
    const size_t SZ = strlen(MSG);
    int ret = write(1, MSG, SZ);
    if (ret == -1) {
        perror("write error");
    }
    _exit(128+sig);
}

void clearStdin() {
    char bufLeft[MAX_LINE];
    int nbCharLeft = read(0, bufLeft, MAX_LINE);
    while (nbCharLeft > 0 && bufLeft[nbCharLeft-1] != '\n') {
        read(0, bufLeft, MAX_LINE);
    }
    printf("stdin was emptied\n");
}

int main (int argc, char** argv) {

    printf("ce programme transforme les lettres minuscules en majuscules.\nSaisissez vos lignes de max %d caracteres. Ctrl-D pour arreter.\n", MAX_LINE);

    int fds[2];
    int ret = pipe(fds);
    if (ret == -1) {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    int childPid = fork();
    if (childPid == -1) {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    if (childPid) {
        
        //arm the signal
        struct sigaction action = {0};
        action.sa_handler = sigHandler;
        ret = sigfillset(&action.sa_mask);
        if(ret == -1) perror("sigfillset");
        action.sa_flags = 0;
        ret = sigaction(SIGPIPE, &action, NULL);
        if(ret == -1) perror("sigaction");

        //close unused fd
        ret = close(fds[0]);
        if (ret == -1) {
            perror("close error");
            exit(EXIT_FAILURE);
        }

        char bufRd[MAX_LINE];
        int nbRd = read (0, bufRd, MAX_LINE);
        if (nbRd == -1) {
            perror("read error");
            exit(EXIT_FAILURE);
        }
        while (nbRd > 0) {
            if (bufRd[nbRd - 1] == '\n') {
                int nbWr = write(fds[1], bufRd, nbRd);
                if (nbWr != nbRd) {
                    perror("write error");
                    exit(EXIT_FAILURE);
                }
                nbRd = read(0, bufRd, MAX_LINE);
                if(nbRd == -1) {
                    perror("read error");
                    exit(EXIT_FAILURE);
                }
            } else {
                perror("line is too big.");
                clearStdin();
                exit(EXIT_FAILURE);
            }
        }
        ret = close(fds[1]);
        if (ret == -1) {
            perror("close error");
            exit(EXIT_FAILURE);
        }
        int status;
        int res = waitpid(childPid, &status, 0);
        if (res == -1) {
            perror("wait error");
            exit(EXIT_FAILURE);
        }

    } else {
        //close unused pipe
        ret = close(fds[1]);
        if (ret == -1) {
            perror("close error");
            exit(EXIT_FAILURE);
        }
        ret = close(fds[0]);
        if (ret == -1) {
            perror("close error");
            exit(EXIT_FAILURE);
        }
        char pipeRd[MAX_LINE];
        int nbRd = read(fds[0], pipeRd, MAX_LINE);
        if (nbRd == -1) {
            perror("read error");
            exit(EXIT_FAILURE);
        }
        while (nbRd > 0) {
            for (int i = 0; i < nbRd; i++) {
                if (pipeRd[i] > 96 && pipeRd[i] < 123) {
                    pipeRd[i] -= 32;
                }
            }
            int nbWr = write (1, pipeRd, nbRd);
            if (nbWr != nbRd) {
                perror ("write error");
                exit(1);
            }
            nbRd = read(fds[0], pipeRd, MAX_LINE);
            if (nbRd == -1) {
                perror("read error");
                exit(EXIT_FAILURE);
            }
        }
        ret = close(fds[0]);
        if (ret == -1) {
            perror("close error");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
}