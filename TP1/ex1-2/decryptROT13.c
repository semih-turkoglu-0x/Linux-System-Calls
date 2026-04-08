#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "cryptROT13.h"

int main() {
    printf("Veuillez rentrez une chaine de caracteres : \n");
    char* line = readLine();
    if (line == NULL) exit(1);

    char* decryptLine = decrypt(line);
    printf("voici la chaine dechiffree :\n%s\n", decryptLine);

    free(line);
    free(decryptLine);

    exit(0);
}