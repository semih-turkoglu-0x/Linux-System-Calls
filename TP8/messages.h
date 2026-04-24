#ifndef _MESSAGES_H_
#define _MESSAGES_H_

#define SERVER_PORT 21000    // Utilisez un port de votre machine
#define SERVER_IP "127.0.0.1" /* localhost */
#define MAX_PSEUDO 256

typedef enum
{
  INSCRIPTION_REQUEST = 10,
  INSCRIPTION_OK = 11,
  INSCRIPTION_KO = 12
} Code;

/* struct message used between server and client */
typedef struct
{
  char messageText[MAX_PSEUDO];
  int code;
} StructMessage;

#endif
