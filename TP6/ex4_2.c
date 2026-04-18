#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "utils.h"

void handler (int sig) {
    char* msg = " Signal '";
    swrite(1, msg, strlen(msg));
    msg = strsignal(sig);
    swrite(1, msg, strlen(msg));
    msg = "' recu ";
    swrite(1, msg, strlen(msg));
}

int main () {
    pid_t pid = getpid();
    printf("[%d] Hello, I am timer ;)\n", pid);

    struct sigaction action = {0};
    action.sa_handler = handler;

    for (int i = 0; i<32; i++) {
        int res = sigaction(i, &action, NULL);
        if (res != 0) {
            printf("Signal %d (%s) non capture\n", i, strsignal(i));
        }
    }
    printf("\n");

    char c = '.';
    while (1) {
        int res = write(1, &c, sizeof(char));
        if (res == -1 && errno != EINTR) {
            perror("erreur write\n");
            exit(1);
        }
        sleep(1);
    }
}