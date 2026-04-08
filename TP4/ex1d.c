#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main () {
    printf("trois... deux... un...\n");
    int childId = fork();
    if (childId == 0) {
        printf("partez !\n");
    }
}