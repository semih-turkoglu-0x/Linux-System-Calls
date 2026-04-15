#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define MSG_SIZE 30

void childFunction (void * arg1, void* arg2) {

    int* pipePF = arg1;
    int* pipeFP = arg2;

    sclose(pipePF[1]);
    sclose(pipeFP[0]);

    int val;
    int sum = 0;
    int count = 0;
    double avg;

    while (sread(pipePF[0], &val, sizeof(int))) {
        sum += val;
        count ++;
        nwrite(pipeFP[1], &sum, sizeof(int));
    }
    if (count > 0) {
        avg = (double) sum / count;
    }
    nwrite (pipeFP[1], &avg, sizeof(double));
    sclose(pipePF[0]);
    sclose(pipeFP[1]);
    
}

int main (int argc, char** argv) {
    int pipePF[2];
    spipe(pipePF);
    int pipeFP[2];
    spipe(pipeFP);

    fork_and_run2(childFunction, pipePF, pipeFP);

    sclose(pipePF[0]);
    sclose(pipeFP[1]);

    int value;
    int sum = 0;
    
    printf("veuillez entrer des entiers, Ctrl-D pour terminer : \n");
    while ((scanf("%d", &value)) != EOF ){
        nwrite(pipePF[1], &value, sizeof(int));
        sread(pipeFP[0], &sum, sizeof(int));

        char msg[MSG_SIZE];
        sprintf(msg, "sum = %d\n", sum);
        nwrite(1, msg, strlen(msg));
    }

    sclose(pipePF[1]);

    double avg;
    sread(pipeFP[0], &avg, sizeof(double));

    char msg[MSG_SIZE];
    sprintf(msg, "\n--> average = %.2f\n", avg);
    nwrite(1, msg, strlen(msg));

    sclose(pipeFP[0]);
}
    