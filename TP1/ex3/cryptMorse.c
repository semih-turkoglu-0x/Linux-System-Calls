#include <stdlib.h>
#include <stdio.h>

static char morse[26] = 
{'.-','-...', '-.-.', '-..', '.',
'..-.', '--.', '....', '..', '.---',
'-.-', '.-..', '--', '-.', '---', 
'.--.', '--.-', '.-.', '...', '-',
'..-', '...-', '.--', '-..-', '-.--', '--..'
};

static char* morse (char* msg) {
    int sz = strlen(msg);
    char* res = malloc ((sz * 2)*sizeof(char))
}