#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {

    char* str1 = "1 2 3\n";
    char* str2 = "4 5 6\n";

    int childId = fork();
    if (childId == -1) {
        perror("fork failed");
        exit(1);
    }

    if (childId) {
        if ((write(1, str1, strlen(str1))) == -1) {
            perror("write failed");
            exit(15);
        }
    } else {
        if ((write(1, str2, strlen(str2))) == -1) {
            perror("write failed");
            exit(16);
        }
    }
}