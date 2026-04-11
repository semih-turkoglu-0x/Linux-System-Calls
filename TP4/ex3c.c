#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main () {
    int childId = fork();
    if (childId == -1) {
        perror("fork failed");
        exit(1);
    }
    if (childId != 0) {
        int exitStatus;
        wait(&exitStatus);
        printf("1 2 3\n");
        printf("%d\n", WEXITSTATUS(exitStatus));
    } else {
        printf("4 5 6\n");
        exit(23);
    }
}
//options : WEXITSTATUS