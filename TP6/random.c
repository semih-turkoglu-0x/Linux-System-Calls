#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "utils.h"

/// Déclaration de constantes

#define MAX_VAL   1000000000   // 1 milliard
#define SEUIL     MAX_VAL/2
#define POURCENT  SEUIL/(double)MAX_VAL*100

volatile sig_atomic_t afficher_stats = 0;
volatile sig_atomic_t fin_processus = 0;

void child (void* arg1, void *arg2);
void sigint_handler(int signum);
void sigtstp_handler(int signum);

/// Programme principal
int main(int argc, char** argv) 
{
    printf("RAND_MAX = %d\n", RAND_MAX);
    printf("MAX_VAL  = %d  ==> valeurs aléatoires entre %d et %d\n", MAX_VAL, 0, MAX_VAL-1);
    printf("SEUIL = MAX_VAL/2 = %d  ==> valeurs inférieures au seuil: %.0f%%\n\n", SEUIL, POURCENT);
    printf("Pour une suite uniformément répartie dans l'intervalle [0,MAX_VAL[, "\
        "le pourcentage de valeurs aléatoires inférieures "\
        "au seuil MAX_VAL/2 devrait correspondre à %.2f%%.\n", POURCENT);
    printf("Vérifions si c'est bien le cas.\n\n");

    sigset_t blocked;
    ssigemptyset(&blocked);
    ssigaddset(&blocked, SIGINT);
    ssigaddset(&blocked, SIGTSTP);
    ssigprocmask(SIG_BLOCK, &blocked, NULL);

    int pipe1[2];
    spipe(pipe1);
    int formule = 1;
    pid_t pid1 = fork_and_run2(child, &formule, pipe1);

    int pipe2[2];
    spipe(pipe2);
    formule = 2;
    pid_t pid2 = fork_and_run2(child, &formule, pipe2);

    sclose(pipe1[0]);
    sclose(pipe2[0]);

    ssigaction(SIGTSTP, sigtstp_handler);

    ssigdelset(&blocked, SIGINT);
    ssigprocmask(SIG_UNBLOCK, &blocked, NULL);
    
    int random;
    while(!fin_processus) {
        random = rand();
        nwrite(pipe1[1], &random, sizeof(int));
        nwrite(pipe2[1], &random, sizeof(int));
    }

    sclose(pipe1[1]);
    sclose(pipe1[1]);

    swaitpid(pid1,NULL,0);
    swaitpid(pid2,NULL,0);
    printf("Fin du père\n");
}

void child (void* arg1, void* arg2)
{
    ssigaction(SIGINT, sigint_handler);

    sigset_t blocked;
    ssigemptyset(&blocked);
    ssigaddset(&blocked, SIGINT);
    ssigprocmask(SIG_UNBLOCK, &blocked, NULL);

    int formule = *(int*)arg1;
    int *pipefd = arg2;

    sclose(pipefd[1]);

    int randVal, res;
    double nInf = 0;

    double cnt = 0;
    int nread;

    while ((nread = read(pipefd[0], &randVal, sizeof(int))) != 0) {
        if (nread == -1) continue;

        // génération d'une valeur dans l'intervalle [0,MAX_VAL[ 
        if (formule == 1)  // formule 1 simple
            res = randVal % MAX_VAL;
        else  // formule 2 complexe
            res = (int)(randVal/(RAND_MAX+1.0)*MAX_VAL);        

        // mise à jour des stats
        if (res < SEUIL)
            nInf++;
        cnt++;

        // affichage des stats
        if (afficher_stats) {
            printf("\nFILS%d: %.0f valeurs reçues --> %.4f%%" \
                   " valeurs générées inférieures au seuil\n", formule, cnt, nInf/cnt*100);
            afficher_stats = 0;
        }
    }

    sclose(pipefd[0]);

    printf("Fin du fils %d\n", formule);
}

void sigtstp_handler (int signum) {
    fin_processus = 1;
}

void sigint_handler (int signum) {
    afficher_stats = 1;
}