#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "utils.h"

#define SHM_KEY   1234
#define A_SEM_KEY 667788
#define B_SEM_KEY 998877
#define PERM 0666

#define NLOOPS 100000

struct data {
    int A;   // ressource partagée protégée par le sémaphore semA
    int B;   // ressource partagée protégée par le sémaphore semB
};

void child_handler()
{
    int semA = sem_get(A_SEM_KEY, 1);
    int semB = sem_get(B_SEM_KEY, 1);

    int shm_id = sshmget(SHM_KEY, sizeof(struct data), 0);
    struct data *p = sshmat(shm_id);

    for (int i = 0; i <= NLOOPS; i++) {
        if (i % 100 == 0) {
          colorOn(0,CYAN_TEXT);
          printf("[CHILD ] i=%d  A=%d  B=%d\n", i, p->A, p->B);
        }

        sem_down0(semB);
        sem_down0(semA);

        /**** DEBUT DE SECTION CRITIQUE ***/
        // transfert de B vers A
        p->A += 1;
        p->B -= 1;
        /**** FIN DE SECTION CRITIQUE *****/

        sem_up0(semA);
        sem_up0(semB);
    }

    sshmdt(p);
}

int main(int argc, char *argv[])
{
    int semA = sem_create(A_SEM_KEY, 1, PERM, 1);
    int semB = sem_create(B_SEM_KEY, 1, PERM, 1);

    int shm_id = sshmget(SHM_KEY, sizeof(struct data), IPC_CREAT | PERM);
    struct data *p = sshmat(shm_id);

    p->A = 0;
    p->B = 0;

    pid_t pid = fork_and_run0(child_handler);

    for (int i = 0; i <= NLOOPS; i++) {
        if (i % 100 == 0) {
          colorOn(0,YELLOW_TEXT);
          printf("[PARENT] i=%d  A=%d  B=%d\n", i, p->A, p->B);
        }

        sem_down0(semB);
        sem_down0(semA);

        /**** DEBUT DE SECTION CRITIQUE ***/
        // transfert de A vers B
        p->A -= 1;
        p->B += 1;
        /**** FIN DE SECTION CRITIQUE *****/

        sem_up0(semA);
        sem_up0(semB);
    }

    swaitpid(pid, NULL, 0);

    // Facultatif : nettoyer
    sshmdelete(shm_id);
    sem_delete(semA);
    sem_delete(semB);

    sshmdt(p);
}


/*
  Remarque:
    Les sémaphores permettent de protéger les sections critiques,
    qui correspondent à deux opérations à somme nulle.
    Sans eux, les données seraient corrompues (sommes non nulles).
    Il suffit de supprimer les sémaphores pour le constater.
*/