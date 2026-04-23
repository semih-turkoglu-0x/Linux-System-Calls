#include <stdio.h>

#include "utils.h"
#include "ipc_conf.h"

#define ARRAY 10

int main() {
    int semid = sem_get(SEM_KEY, 1);
    int shmid = sshmget(SHM_KEY, 2 * sizeof(int), 0);

    int *number = sshmat(shmid);
    int* ecran = number + 1;

    sem_down0(semid);

    if (*ecran < *number) {
        (*ecran)++;
        printf("%d\n", *ecran);
    } else {
        printf("il n'y a plus personne!\n");
    }

    sem_up0(semid);

    sshmdt(number);

}