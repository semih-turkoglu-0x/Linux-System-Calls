#include <string.h>
#include <unistd.h>
#include <sys/sem.h>
#include "utils.h"

#define MAX 30
#define KEY 123
#define PERM 0666

void childFunction(void* arg) {
    int semid = *(int*) arg;
    pid_t pid = getpid();
    char* msg = "je suis le fils";
    char newString[MAX];
    sprintf(newString, "%s %d\n", msg, pid);
    sem_down0(semid);
    for (int i = 0; i <= 2; i++) {
        swrite(1, newString, strlen(newString));
        sleep(1);
    }
    sem_up0(semid);
}

int main () {
    int semid = sem_create(KEY, 1, PERM, 1);

    int fchild = fork_and_run1(childFunction, &semid);
    int schild = fork_and_run1(childFunction, &semid);

    swaitpid(fchild, NULL, 0);
    swaitpid(schild, NULL, 0);
    sem_delete(semid);
}