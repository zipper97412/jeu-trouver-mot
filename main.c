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
#include "coreLoop.h"

const char phrases[MAXPH][PHLEN]= {"Cette /1ecole n'est pas specialisee dans la /2medecine ni dans l'aviation...         ",
						"Cela fait moins de /120ans que /3Mitterand n'est plus parmi nous.         ",
						"A la fin de la /3guerre , /1l'informatique n'en etait qu'a ses premices.         ",
						"Les /1ingenieurs participent a la construction d'un monde meilleur.         ",
						"Malgre toutes les avancees, le /2SIDA existe encore.         ",
						"Au /3moyen-age , a des fins /2therapeutiques , des sangsues etaient utilisees         ",
						"Les /1reseaux sociaux peuvent etre /2addictifs , voire dangereux.         ",
						"Les /2blesses de /3guerre etaient appeles les gueules cassees.         ",
						"Pendant la /3prehistoire est apparu le feu.         ",
						"/1L'ESISAR se preoccupe du /2bien-etre de chacun.         ",
						"Peu a peu, /1l'electronique regit de plus en plus notre mode de vie.         ",
						"Les effets des /2medicaments prescrits a Sanchez furent concluants.         ",
						"C'est en /31789 que le peuple se souleva pour faire valoir ses droits aux yeux du monde entier.         ",
						"Le petrole est devenu a notre /3epoque indispensable pour le monde tel qu'il est maintenant.         "
						};
PLAYER tabJoueur[MAXPL];
THEME tabTheme[MAXTH];

void main(void)
{
	char valide = '0';
	char i=0, nbJoueur=0;
	char vitesse;
	init_ports();
	UART_init();
	
	
	while (1)
	{
		valide = '0';
		for(i=0;i<MAXPL;i++) {
			tabJoueur[i].actif = 0;
		}
		for(i=0;i<MAXTH;i++) {
			tabTheme[i].actif = 0;
		}
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
					UART_putstring("Le joueur 3 rentre en lice ! \r\n");
					tabJoueur[2].actif=1;
					nbJoueur++;
			}
			valide = '1';
		}
		while (Etat_BP04() == 0);
		UART_putstring("\nVeuillez maintenant selectionner la vitesse de defilement a l aide du potentiometre\r\n");
		UART_putstring("Validez la vitesse en appuyant sur le bouton 4\n");
		
		
		t4_reset();
		t4_setARR(234);
		t4_setPSCR(0x07);
		vitesse = potentiometre();
		t4_reset();
		
		while (Etat_BP04() == 0);
		
		
		if (tabJoueur[0].actif == 1)
		{
			UART_putstring("\r\nJoueur 1, choisissez un theme en appuyant sur le bouton correspondant\r\n");
			deter_theme(0, tabJoueur);
		}
		if (tabJoueur[1].actif == 1)
		{
			UART_putstring("\r\nJoueur 2, choisissez un theme en appuyant sur le bouton correspondant\r\n");
			deter_theme(1, tabJoueur);
		}
		if (tabJoueur[2].actif == 1)
		{
			UART_putstring("\r\nJoueur 3, choisissez un theme en appuyant sur le bouton correspondant\r\n");
			deter_theme(2, tabJoueur);
		}
		
		for(i=0;i<MAXPL;i++) {
			if (tabJoueur[i].actif == 0) {
				tabTheme[tabJoueur[i].idTheme].actif=1;
				tabTheme[tabJoueur[i].idTheme].idPlayer=i;
			}
		}
		
		
		while(nb_appui() != 0);
		
		UART_putstring("\nAppuyez tous en meme temps sur votre bouton lorsque vous serez prets.\r\n");
		
		while(nb_appui() < nbJoueur);
		
		UART_putstring("Vous pouvez maintenant tous relacher\r\n\n");
		
		while(nb_appui() != 0);
		
		UART_putstring("ATTENTION !!! LE JEU VA COMMENCER ! \r\nREGARDER BIEN L'AFFICHEUR ! \r\n\n");
		
		decompte();
		
		roundLoop(tabJoueur, tabTheme, phrases, vitesse);
		
		
		
	}
}