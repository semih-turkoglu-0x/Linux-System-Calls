#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "cryptPolybe.h"

static char square[8][8] =
{{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
{'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
{'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
{'Y', 'Z', '0', '1', '2', '3', '4', '5'},
{'6', '7', '8', '9', ' ', '!', '"', '#'},
{'$', '%', '&', '\'', '(', ')', '*', '+'},
{',', '-', '.', '/', ':', ';', '<', '='},
{'>', '?', '@', '[', '\\', ']', '^', '_'}};

static char* polybe(char* msg) {
    int sz = strlen(msg);

    char* res = malloc (((sz*2)+1) * sizeof(int));
    if (res == NULL) {
        perror("malloc error\n");
        exit(1);
    }
    
    for(int i=0; i++ ; i < 8) {
        for(int j = 0; j++ ; j < 8){
            
        }
    }
}