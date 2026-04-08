#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "biblio.h"
#include "utils.h"

#define BUF_SIZE TITLE+2

static char* genres[GENRES_NUM] = 
{ "Bande dessinee", "Poesie", "Theatre", "Roman",
    "Roman historique", "Litterature francaise",
    "Litterature etrangere", "Sciences", "Informatique",
    "Science-fiction", "Sante", "Histoire"
};

bool lireLivre (Livre* l) {
    char line[BUF_SIZE];

    if (readLimitedLine(line, TITLE+2) <= 0) return false;
    strncpy(l->title, line, TITLE+2);

    if (readLimitedLine(line, AUTHORS+2) <= 0) return false;
    strncpy(l->authors, line, AUTHORS+2);

    if(scanf("%ld\n", &l->isbn) != 1) return false;

    if (readLimitedLine(line, EDITOR+2) <= 0) return false;
    strncpy(l->editor, line, EDITOR+2);

    if (scanf("%d\n", &l->editionYear) != 1) return false;

    if (readLimitedLine(line, BUF_SIZE) <= 0) return false;
    if((l->genre = str2genre(line)) == -1) return false;

    return true;
}

Genre str2genre (char* msg) {
    for (Genre g = 0; g < GENRES_NUM; g++) {
        if(!strcmp(msg, genres[g])) {
            return g;
        }
    }
    return -1;
}

char* genre2str (Genre ge) {
    int nbGenres = sizeof(genres)/sizeof(char*);
    if (ge < 0 || ge > nbGenres) return NULL;
    return genres[ge];
}

char* livre2string (char* s, Livre l) {
    sprintf(s, "%-40s -%40s\n%ld\n%-40s %d\n%s\n", l.title, l.authors, l.isbn, l.editor, l.editionYear, genre2str(l.genre));
    return s;
}

void afficherBib(const Livre* bib, int t) {
    char line[TITLE];
    for (int i = 0; i < t; i++) {
        printf("\t%s\n", livre2string(line, bib[i]));
        printf("----------------------------------");
    }
}

bool ajouterLivre(Livre** bib, Livre l, int* nbreL, int* taille){
    if (*taille == 0) { //tableau non initialisé, memory allocation initiale - taille = 3 est un choix arbitraire
        if((*bib = (Livre*)malloc((*taille=3)*sizeof(Livre))) == NULL){
            perror("malloc error\n");
            return false;
        }
    } else if(*taille == *nbreL) {
            *taille *= 2;
            if ((*bib = (Livre*)realloc(*bib, *taille * sizeof(Livre))) == NULL) {
                perror("realloc error \n");
                return false;
            }
    }
        (*bib)[*nbreL] = l;
        (*nbreL)++;
        return true;
}
