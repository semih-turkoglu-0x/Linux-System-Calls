#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "ipc_conf.h"

int main (int argc, char** argv) {

    char create[3] = "-c";
    char delete[3] = "-d";

    int semid, shmid;

    if (argc != 2) {
        perror("Usage : ./admin1 -c|-d");
        exit(1);
    }

    if ((strcmp(create, argv[1])) == 0) {
        semid = sem_create(SEM_KEY, 1, PERM, 1);
        shmid = sshmget(SHM_KEY, 2 * sizeof(int), IPC_CREAT | PERM);
        int *ticket = sshmat(shmid);
        *ticket = 1;
    }

    if ((strcmp(delete, argv[1])) == 0) {
        shmid = sshmget(SHM_KEY, sizeof(int), 0);
        semid = sem_get(SEM_KEY, 1);
        sshmdelete(shmid);
        sem_delete(semid);
    }
}