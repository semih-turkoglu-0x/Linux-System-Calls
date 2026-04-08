#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

#define BUFFERSIZE 10

int main () {
    printf("entrez une chaine d'au plus 10 caracteres\n");
    char buf[BUFFERSIZE];
    int nbCharRead;
    int nbCharWr;
    while ((nbCharRead = read(0, buf, BUFFERSIZE)) > 0) {
        checkNeg(nbCharRead, "read error");

        nbCharWr = write(1, buf, nbCharRead);
        checkNeg(nbCharWr, "write error");
    }
   
    checkNeg(nbCharRead, "read error");
    exit(0);
}