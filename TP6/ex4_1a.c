#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

int main () {
    int childPid = sfork();
    if (childPid) {
        exit(EXIT_SUCCESS);
    } else {
        while (1) {
            sleep(1);
        }
    }
}