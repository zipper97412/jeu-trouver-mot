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
#include "beep.h"
#include "score.h"

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
	int valide;
	char i=0, nbJoueur=0;
	char vitesse;
	init_ports();
	UART_init();
	Init_Timer2();
	t3_setPSCR(0x0003);
	t3_setARR(0x00F9);
	t4_setARR(234);
	t4_setPSCR(0x07);
	
	
	while (1)
	{
		valide = 0;
		GPIOA->ODR = 0xFF;
		for(i=0;i<MAXPL;i++) 
		{
			tabJoueur[i].actif = 0;
			tabJoueur[i].idJoueur = i;
			tabJoueur[i].idTheme = 5;
			tabJoueur[i].score = 0;
			tabJoueur[i].penality = 0;
		}
		
		for(i=0;i<MAXTH;i++) 
		{
			tabTheme[i].actif = 0;
		}
		UART_putstring("\r\n\n\n\n\n==================================== GRENOBLE INP ESISAR ====================================\r\n\n                                         \"20 ans\"\r\n\n                                  Jeu : Trouver les mots\r\n\nAppuyez sur Espace pour commencer le jeu\r\n\n");
		while(UART_getchar()!= ' ');
		//clear_uart();
		UART_putstring("\rJoueurs : Presentez-vous \r\n");
		UART_putstring("Appuyez sur les boutons 1, 2 ou 3\r\n");
		UART_putstring("Une fois tous les joueurs inscrits, appuyez sur Espace pour valider\r\n\n");
		
		while( (UART_getchar()!= ' ' || valide == 0))  
		{
			//H ET T°
			if ( (Etat_BP01() == 0) && tabJoueur[0].actif == 0 )
			{
					UART_putstring("Le joueur 1 rentre en lice ! \r\n");
					tabJoueur[0].actif=1;
					GPIOA->ODR &= 0xF7 ;
					nbJoueur++;
					valide =1;
			}
			if ( (Etat_BP02() == 0) && tabJoueur[1].actif == 0 )
			{
					UART_putstring("Le joueur 2 rentre en lice ! \r\n");
					tabJoueur[1].actif=1;
					GPIOA->ODR &= 0xEF ;
					nbJoueur++;
					valide =1;
			}
			if ((Etat_BP03() == 0) && tabJoueur[2].actif == 0 )
			{
					UART_putstring("Le joueur 3 rentre en lice ! \r\n");
					tabJoueur[2].actif=1;
					GPIOA->ODR &= 0xDF ;
					nbJoueur++;
					valide =1;
			}
		}

		UART_putstring("\nVeuillez maintenant selectionner la vitesse de defilement a l'aide du potentiometre\r\n");
		UART_putstring("Validez la vitesse en appuyant sur Espace\n");
		
		t4_reset();
		vitesse = potentiometre();
		t4_reset();
		
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
		
		for(i=0;i<MAXPL;i++) 
		{
			if (tabJoueur[i].actif != 0) 
			{
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

		disp_score(tabJoueur);
		
		marche_imperiale();
	}
}