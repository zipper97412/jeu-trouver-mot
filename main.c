/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include "stm8s.h"
#include "stm8s_conf.h"
#include "bouton.h"
#include "timer3.h"
#include "afficheur.h"
#include "uart.h"
#include "ports.h"
#include "potentiometre.h"
#include "timer4.h"
#include "datastruct.h"
#include "theme.h"
#include "prejeu.h"

void main(void)
{
	char valide = '0';
	char i=0, nbJoueur=0;
	PLAYER tabJoueur[3];
	init_ports();
	UART_init();
	
	while (1)
	{
		valide = '0';
		while(i!=3)
		{
			tabJoueur[i].actif = 0;
			tabJoueur[i].idTheme = 0;
			i++;
		}
		i=0;
		while(Etat_BP04() == 0);
		UART_putstring("Joueurs : Presentez-vous \r\n");
		UART_putstring("Appuyez sur les boutons 1, 2 ou 3\r\n");
		UART_putstring("Une fois tous les joueurs inscrits, appuyez sur le bouton 4 pour valider\r\n\n");
		while(Etat_BP04() != 0 || valide == '0' )
		{
			//H ET T°
			if ( (Etat_BP01() == 0) && tabJoueur[0].actif == 0 )
			{
					UART_putstring("Le joueur 1 rentre en lice ! \r\n");
					tabJoueur[0].actif=1;
					nbJoueur++;
			}
			if ( (Etat_BP02() == 0) && tabJoueur[1].actif == 0 )
			{
					UART_putstring("Le joueur 2 rentre en lice ! \r\n");
					tabJoueur[1].actif=1;
					nbJoueur++;
			}
			if ((Etat_BP03() == 0) && tabJoueur[2].actif == 0 )
			{
					UART_putstring("Le joueur 3 rentre en lice ! \r\n\n");
					tabJoueur[2].actif=1;
					nbJoueur++;
			}
			valide = '1';
		}
		while (Etat_BP04() == 0);
		UART_putstring("Veuillez maintenant selectionner la vitesse de defilement a l aide du potentiometre\r\n");
		UART_putstring("Validez la vitesse en appuyant sur le bouton 4\n");
		
		
		t4_reset();
		t4_setARR(234);
		t4_setPSCR(0x07);
		potentiometre();
		t4_reset();
		
		while (Etat_BP04() == 0);
		
		
		if (tabJoueur[0].actif == 1)
		{
			UART_putstring("\r\nJoueur 1, choisissez un theme en appuyant sur le bouton correspondant\r\n");
			deter_theme(1, tabJoueur);
		}
		if (tabJoueur[1].actif == 1)
		{
			UART_putstring("\r\nJoueur 2, choisissez un theme en appuyant sur le bouton correspondant\r\n");
			deter_theme(2, tabJoueur);
		}
		if (tabJoueur[2].actif == 1)
		{
			UART_putstring("\r\nJoueur 3, choisissez un theme en appuyant sur le bouton correspondant\r\n");
			deter_theme(3, tabJoueur);
		}
		
		UART_putstring("\n Appuyez tous en meme temps sur votre bouton lorsque vous serez prets.\r\n");
		
		while(nb_appui() < nbJoueur);
		
		UART_putstring("Vous pouvez maintenant tous relacher\r\n\n");
		
		while(nb_appui() != 0);
		
		UART_putstring("ATTENTION !!! LE JEU VA COMMENCER ! \r\nREGARDER BIEN L'AFFICHEUR ! \r\n\n");
		
		decompte();
	}
}
