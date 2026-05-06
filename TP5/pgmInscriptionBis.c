#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils.h"
#include "inscriptionRequest.h"

void childFunction(void* ffds, void *sfds)
{
    int* ptr1 = ffds;
    int* ptr2 = sfds;
    sclose(ptr1[1]);
    sclose(ptr2[0]);

    int nbInscrits = 0;
    InscriptionRequest ir;
    ssize_t nbRd;

    while ((nbRd = sread(ptr1[0], &ir, sizeof(ir))) == sizeof(ir)) {
        if (ir.nbYearPastInEducation < 3) {
            nbInscrits++;
        }
    }
        
    sclose(ptr1[0]);
    swrite(ptr2[1], &nbInscrits, sizeof(int));
    sclose(ptr2[1]);
}

int main (int argc, char** argv)
{
    int ffds[2];
    int sfds[2];

    spipe(ffds);
    spipe(sfds);

    InscriptionRequest ir;
    ssize_t nbRd;
    int nbInscrits = 0;
    int nbInscritsSon; 

    fork_and_run2(childFunction, ffds, sfds);

    int count = 1;

    while ((nbRd = sread(STDIN_FILENO, &ir, sizeof(ir))) == sizeof(ir)) {
        if((count % 2) == 0) {
            swrite(ffds[1], &ir, sizeof(ir));
            printf("Attente trt fils : %s %d\n", ir.name, ir.nbYearPastInEducation);
        } else {
            printf("Trt par le pere : %s %d\n", ir.name, ir.nbYearPastInEducation);
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
}