/* UART */

#include "stm8s_type.h"

#ifndef UART_H
#define UART_H

#define ERROR  1
#define SUCCESS  0 
#define EMPTY 0

/**
\brief cette fonction permet d'initialiser l'UART
*/
void UART_init(void);


/**
\brief reçoit un caractere par l'uart
\return le caractère reçu, 0 sinon
*/
char UART_getchar(void);


/**
\brief envoie un caractère par l'uart
\param car le caractere a envoyer
\return 0 si tout s'est bien passe, 1 sinon
*/
u8 UART_putchar(char car);


/**
\brief envoie une chaine de caractere
\param chaine la chaine a envoyer
\return 0 si tout s'est bien passe, 1 sinon
*/
//u8 UART_putstring(char* chaine);
u8 UART_putstring(char *chaine);


#endif
