#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main () {
    
    struct sigaction action = {0};
    action.sa_handler = SIG_IGN;
    ret = sigfillset(&action.sa_mask);
    if(ret == -1) perror("sigfillset");
    action.sa_flags = 0;
    ret = sigaction(SIGHUP, &action, NULL);
    if(ret == -1) perror("sigaction");
    execvp(argv[1], argv+1);
    perror("exec error");
    exit(1);
}