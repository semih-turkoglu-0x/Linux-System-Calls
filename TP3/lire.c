#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

#define BUFFERSIZE 10

void clearStdin () {
    char buf[BUFFERSIZE];
    int nbCharRead = read(0, buf, BUFFERSIZE);
    while (nbCharRead > 0 && buf[nbCharRead-1] != '\n') {
        nbCharRead = read(0, buf, BUFFERSIZE);
    }
    checkNeg(nbCharRead, "error reading stdin");
}

int main () {
    printf("entrez une chaine d'au plus 10 caracteres\n");
    char buf[BUFFERSIZE];
    int nbCharRead;
    int nbCharWr;
    while ((nbCharRead = read(0, buf, BUFFERSIZE)) > 0) {
        if (buf[nbCharRead - 1] == '\n') {
            nbCharWr = write(1, buf, nbCharRead);
            checkCond(nbCharWr != nbCharRead, "error writing on stdout");
        } else {
            printf("erreur : ligne introduite fait plus de 10 caracteres\n");
            exit(0); //traitement 1
            //clearStdin(); traitement 2
        }
        nbCharRead = read(0, buf, BUFFERSIZE);
    }
   
    checkNeg(nbCharRead, "read error");
    exit(0);
}