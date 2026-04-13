#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"

#define MAX 20

int main (int argc, char** argv) {
    printf("saisissez le nom du fichier :\n");
    char bufRd[MAX];
    int nbChar = sread(0, bufRd, MAX);
    bufRd[nbChar - 1] = '\0';
    int fd = sopen(bufRd, O_RDWR |  O_CREAT | O_TRUNC, 0744);
}
