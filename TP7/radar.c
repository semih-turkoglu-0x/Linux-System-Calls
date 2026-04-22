#include <sys/shm.h>
#include <unistd.h>
#include "utils.h"

#define KEY 123
#define PERM 0666

int main () {
    int memid = shmget (KEY, sizeof(int), IPC_CREAT | PERM);
    checkNeg(memid, "shmget error");
    int *addr = shmat(memid, NULL, 0);
    checkNeg(*addr, "shmat error");
    int counter = 0;
    while (counter <= 20) {
        *addr = randomIntBetween(0, 1000);
        counter++;
        sleep(3);
    }
    
    //int ret = shmctl(memid, IPC_RMID, NULL);
    //checkNeg(ret, "shmctl");

    int ret = shmdt(addr);
    checkNeg(ret, "shmdt");
}