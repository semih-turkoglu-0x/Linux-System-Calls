#include <string.h>
#include <unistd.h>
#include "utils.h"

#define MAX 30

void childFunction() {
    pid_t pid = getpid();
    char* msg = "je suis le fils";
    char newString[MAX];
    sprintf(newString, "%s %d\n", msg, pid);
    for (int i = 0; i <= 2; i++) {
        swrite(1, newString, strlen(newString));
        sleep(1);
    }
}

int main () {
    int fchild = fork_and_run0(childFunction);
    int schild = fork_and_run0(childFunction);

    swaitpid(fchild, NULL, 0);
    swaitpid(schild, NULL, 0);
}