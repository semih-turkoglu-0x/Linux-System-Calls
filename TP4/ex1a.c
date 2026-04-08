#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main () {
    int a = 5;
    int childId = fork();
    if (childId == -1) {
        perror("fork failed\n");
    }
    printf("%d\n", childId);

    if(childId != 0) {
        int b = a * 5;
        printf("valeur de a et b chez le parent:\na:%d\nb:%d\n",a, b);
    } else {
        int b = a * 2;
        printf("valeur de a et b chez le fils:\na:%d\nb:%d\n", a, b);
    }
}