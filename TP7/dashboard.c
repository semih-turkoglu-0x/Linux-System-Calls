#include <sys/shm.h>
#include <unistd.h>
#include "utils.h"

#define KEY 123

int main () {
    int memid = shmget(KEY, sizeof(int), 0);
    checkNeg(memid, "shmget");

    int *addr = shmat(memid, NULL, 0);
    checkNeg(*addr, "shmat error");

    int counter = 0;
    while (counter <= 12) {
        printf("valeur de la shm : %d\n", *addr);
        counter++;
        sleep(5);
    }

    int ret = shmdt(addr);
    checkNeg(ret, "shmdt");
}