#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

#define BUF_SIZE 80

void checkArgs (int argc, char** argv) {
    if (argc != 3) {
        printf("trop ou pas assez d'arguments. veuillez saisir 2 noms de fichier\n");
        exit(1);
    }
}

void clearStdin() {
    char bufRd[BUF_SIZE];
    int nbCharRd = read(0, bufRd, BUF_SIZE);
    while (nbCharRd > 0 && bufRd[nbCharRd - 1] != '\n') {
        nbCharRd = read(0, bufRd, BUF_SIZE);
    }
    checkNeg(nbCharRd, "Error reading stdin");
    perror("erreur : la ligne introduite fait plus de 80 caracteres.\n");
    exit(0);
}

int main (int argc, char** argv) {
    checkArgs(argc, argv);
    printf("veuillew entrez une ligne d'au plus 80 caracteres\n");
    char bufRd[BUF_SIZE];

    int fd1 = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    int fd2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);

    int nbCharRead = read(0, bufRd, BUF_SIZE);
    while (nbCharRead > 0) {
        if (bufRd[nbCharRead - 1] == '\n') {
            if (bufRd[0] > 97 && bufRd[0] < 123) {
                int writeL = write(fd2, bufRd, nbCharRead);
                checkCond(writeL != nbCharRead, "error writing in file2");
            }
            if (bufRd[0] > 64 && bufRd[0] < 91) {
                int writeU = write(fd1, bufRd, nbCharRead);
                checkCond(writeU != nbCharRead, "error writing in file1");
            }
            nbCharRead = read(0, bufRd, BUF_SIZE);
        } else {
            clearStdin();
        }
    }

    checkNeg(nbCharRead, "error reading in stdin");

    if (close(fd1) != 0) {
        perror("error close fd1\n");
        exit(1);
    }
    if (close(fd2) != 0) {
        perror("error close fd2\n");
        exit(1);
    }

}