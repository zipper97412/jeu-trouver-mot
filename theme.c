#include "theme.h"
#include "bouton.h"
#include "datastruct.h"
#include "uart.h"
#include "afficheur.h"

void deter_theme(int numJoueur, PLAYER *tabJoueur)
{
	char tab[8]="THEME   ";
	while(tabJoueur[numJoueur].idTheme !=0 && tabJoueur[numJoueur].idTheme !=1 && tabJoueur[numJoueur].idTheme !=2 && tabJoueur[numJoueur].idTheme !=3 )
	{
		while( Etat_BP01() == 1 && Etat_BP02() == 1 && Etat_BP03() == 1 );
		if (Etat_BP01() == 0 && tabJoueur[0].idTheme != 0 && tabJoueur[1].idTheme != 0 && tabJoueur[2].idTheme != 0)
		{
			tab[6]='1';
			printtab(tab);
			tabJoueur[numJoueur].idTheme = 0;
			UART_putstring("Vous avez choisi le theme 1 : ACTUALITES\r\n");
			
		}
		if (Etat_BP02() == 0 && tabJoueur[0].idTheme != 1 && tabJoueur[1].idTheme != 1 && tabJoueur[2].idTheme != 1)
		{
			tab[6]='2';
			printtab(tab);
			tabJoueur[numJoueur].idTheme = 1;
			UART_putstring("Vous avez choisi le theme 2 : EVENEMENTS DE L ESISAR\r\n");
		}
		if (Etat_BP03() == 0 && tabJoueur[0].idTheme != 2 && tabJoueur[1].idTheme != 2 && tabJoueur[2].idTheme != 2)
		{
			tab[6]='3';
			printtab(tab);
			tabJoueur[numJoueur].idTheme = 2;
			UART_putstring("Vous avez choisi le theme 3 : L INTERNATIONAL A L ESISAR\r\n");
		}
		if (Etat_BP04() == 0 && tabJoueur[0].idTheme != 3 && tabJoueur[1].idTheme != 3 && tabJoueur[2].idTheme != 3)
		{
			tab[6]='4';
			printtab(tab);
			tabJoueur[numJoueur].idTheme = 3;
			UART_putstring("Vous avez choisi le theme 4 : ELECTRONIQUE ET INFORMATIQUE\r\n");
		}
	}
}		