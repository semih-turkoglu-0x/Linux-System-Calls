#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

#define MAX 1000
#define HEARTS 7

volatile sig_atomic_t hearts = HEARTS;

void sigusr1_handler (int sig) {
    const char* msg1 = "signal SIGUSR1 recu !\n";
    const char* msg2 = "Fin du fils. jai utilise mes 7 vies\n";
    const size_t SZ = strlen (msg1);
    swrite(1, msg1, SZ);
    hearts--;

    if (hearts == 0) {
        const size_t SZ = strlen(msg2);
        swrite(1, msg2, SZ);
        _exit(0);
    }
}

volatile sig_atomic_t end = 0;

void sigchild_handler (int sig) {
    end = 1;
}

int main () {
    struct sigaction action1 = {0};
    action1.sa_handler = sigusr1_handler;
    int ret = sigfillset(&action1.sa_mask);
    checkNeg(ret, "sigfillset error");
    action1.sa_flags = 0;

    struct sigaction action2 = {0};
    action2.sa_handler = sigchild_handler;
    ret = sigfillset(&action2.sa_mask);
    checkNeg (ret, "sigfillset error");
    action2.sa_flags = 0;
    
    ret = sigaction(SIGUSR1, &action1, NULL);
    checkNeg(ret, "error sigaction");
    ret = sigaction(SIGCHLD, &action2, NULL);
    checkNeg(ret, "error sigaction");

    pid_t childPid = sfork();
    if (childPid) {
        int sent = 0;
        while (!end && sent < MAX) {
            ret = kill(childPid, SIGUSR1);
            checkNeg(ret, "kill error");
            sent ++;
        }
        printf("SIGUSR1 envoyes : %d\n", sent);
        exit(EXIT_SUCCESS);
    } else {
        while (1){
            pause();
            printf("vies restantes = %d\n", hearts);
        }
        
    }
}