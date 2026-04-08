#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    char *msg = "trois... deux... un... ";
    write(1, msg, strlen(msg));
    int childId = fork();
    if (childId == 0) {
        char *msg2 = "partez!";
        write(1, msg2, strlen(msg2));
    }
}