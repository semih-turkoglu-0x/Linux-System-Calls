#include <unistd.h>
#include "utils.h"

int main (int argc, char** argv) {
    int pipeFd[2];
    spipe(pipeFd);

    pid_t son1 = fork();

    if (son1 == 0) {
        //enfant 1
        sclose(pipeFd[0]);
        sdup2(pipeFd[1], 1);
        execlp(argv[1], argv[1], NULL);
        perror("exec 1 failed");
        exit(EXIT_FAILURE);
    }

    pid_t son2 = sfork();

    if (son2 == 0) {
        //enfant 2
        sclose(pipeFd[1]);
        sdup2(pipeFd[0], 0);
        execvp(argv[2], &argv[2]);
        perror("exec2 failed");
        exit(EXIT_FAILURE);
    }

    sclose(pipeFd[0]);
    sclose(pipeFd[1]);

    swait(NULL);
    swait(NULL);
}