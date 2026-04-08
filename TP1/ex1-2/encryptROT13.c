#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "cryptROT13.h"

int main () {
    printf("Veuillez rentrez une chaine de caracteres  : \n");
    char* line = readLine();
    if (line == NULL) exit(1);

    char* cryptLine = encrypt(line);
    printf("voici la chaine chiffree :\n%s\n", cryptLine);

    free(line);
    free(cryptLine);

    exit(0);
}