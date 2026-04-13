#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "utils.h"


void childFunction() {
    const char* str1 = "4 5 6\n";
    nwrite(1, str1, strlen(str1));
    exit(13);
}

int main () {
    int childId = fork_and_run0(childFunction);
    int childStatus;
    swaitpid(childId, &childStatus, 0);

    const char* str2 = "1 2 3\n";
    nwrite(1, str2, strlen(str2));

    if (WIFEXITED(childStatus)) {
        printf("child process exited with code : %d\n", WEXITSTATUS(childStatus));
    } else {
        printf("error : child process did not exited the program correctly\n");
    }
}