#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "utils.h"

int main () {
    int childId = sfork();
    if(childId == 0) {
        printf("4 5 6\n");
        exit(13);
    } else {
        int exitStatus;
        wait(&exitStatus);
        printf("1 2 3\n%d\n", WEXITSTATUS(exitStatus));
    }
}