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
        int waitId = wait(NULL);
        printf("1 2 3\n");
    } else {
        printf("4 5 6\n");
    }
}