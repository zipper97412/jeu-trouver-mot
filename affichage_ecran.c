#include "affichage_ecran.h"
#include "uart.h"
#include "datastruct.h"

void affich_ecran(PLAYER* pJoueur)
{
	UART_putstring("Joueur ");
	while( (UART_putchar(pJoueur->idJoueur+0x31)==1) );
	UART_putstring(" : Vous avez trouve le mot ");
	UART_putstring(words[pJoueur->idTheme]);
	UART_putstring("\r\n");
}