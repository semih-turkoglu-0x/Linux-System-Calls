#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

void sigusr1_handler (int sig) {
    const char* msg = "signal SIGUSR1 recu !\n";
    const size_t sz = strlen (msg);
    swrite(1, msg, sz);
    _exit(13);
}

int main () {
    struct sigaction action = {0};
    action.sa_handler = sigusr1_handler;
    int ret = sigfillset(&action.sa_mask);
    checkNeg(ret, "sigfillset error");
    action.sa_flags = 0;
    
    ret = sigaction(SIGUSR1, &action, NULL);
    checkNeg(ret, "error sigaction");

    pid_t childPid = sfork();
    if (childPid) {
        ret = kill(childPid, SIGUSR1);
        checkNeg(ret, "kill error");
        swait(NULL);
        exit(EXIT_SUCCESS);
    } else {
        pause();
        exit(0);
    }
}