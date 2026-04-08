#ifndef _BIBLIO_H_
#define _BIBLIO_H_

#include <stdbool.h>

#define TITLE 128
#define AUTHORS 80
#define EDITOR 50

typedef enum Genre {BD, PO, TH, RO, RH, LF, LE, SC, IN, SF, SA, HI, GENRES_NUM} Genre;

typedef struct Livre {
    char title [TITLE+1];
    char authors [AUTHORS+1];
    long isbn;
    char editor [EDITOR+1];
    int editionYear;
    Genre genre;
} Livre;

bool lireLivre (Livre* l);

Genre str2genre (char* str);

char* genre2str (Genre ge);

char* livre2str (char* s, Livre l);

void afficherBib(const Livre* bib, int t);

bool ajouterLivre(Livre ** bib, Livre l, int* nbreL, int* taille);

#endif