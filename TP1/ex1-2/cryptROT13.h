#ifndef _CRYPTROT13_H_
#define _CRYPTROT13_H_

/** 
 *PRE : msg is not crypted
 *POST : msg is crypted
 */
char* encrypt (char* msg);
/**
 *PRE : msg is crypted
 *POST : msg is not crypted
 */
char* decrypt (char* msg);

#endif