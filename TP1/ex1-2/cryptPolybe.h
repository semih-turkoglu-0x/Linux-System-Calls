#ifndef _CRYPTPOLYBE_H_
#define _CRYPTPOLYBE_H_
/**
 * Crypte une chaîne de caractères avec Polybe
 * PRE: s : chaîne à crypter
 * RES: renvoie une nouvelle chaîne contenant la chaîne s cryptée en Polybe; 
 *      la chaîne ayant été allouée dynamiquement, elle doit être libérée
 */
char* encrypt (char* s);

/**
 * Décrypte une chaîne de caractères cryptée avec la fonction crypt()
 * PRE: s : chaîne à décrypter
 * RES: renvoie une nouvelle chaîne contenant la chaîne s décryptée en Polybe;
 *      la chaîne ayant été allouée dynamiquement, elle doit être libérée
 */
char* decrypt (char* s);
#endif