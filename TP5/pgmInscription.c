#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include "utils.h"
#include "inscriptionRequest.h"

#define BUFFER 4096

int main(int argc, char** argv) {
    int ffds[2];
    int sfds[2];
    InscriptionRequest ir;
    ssize_t nbRd;
    spipe(ffds);
    spipe(sfds);
    int nbInscrits = 0;
    int nbInscritsSon = 0;

    int childPid = sfork();

    if (childPid) {
        sclose(ffds[0]);
        sclose(sfds[1]);
        int count = 1;
        while ((nbRd = sread(STDIN_FILENO, &ir, sizeof(ir))) == sizeof(ir)) {
            if((count % 2) == 0) {
                swrite(ffds[1], &ir, sizeof(ir));
                printf("Attente trt fils : %s $%d\n", ir.name, ir.nbYearPastInEducation);
            } else {
                printf("Trt par le pere : %s $%d\n", ir.name, ir.nbYearPastInEducation);
                if (ir.nbYearPastInEducation < 3) nbInscrits++;
            }
            count++;
        }
        sclose(ffds[1]);
        swait(NULL);
        sread(sfds[0], &nbInscritsSon, sizeof(int));
        sclose(sfds[0]);
        nbInscrits += nbInscritsSon;
        printf("Nb total d'inscrits : %d\n", nbInscrits);
    } else {
        sclose(ffds[1]);
        sclose(sfds[0]);
        while ((nbRd = sread(ffds[0], &ir, sizeof(ir))) == sizeof(ir)) {
            if (ir.nbYearPastInEducation < 3) {
                nbInscritsSon++;
            }
        }
        sclose(ffds[1]);
        swrite(sfds[1], &nbInscritsSon, sizeof(int));
        sclose(sfds[1]);
    }
}