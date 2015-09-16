#include "stm8s.h"
#include "bouton.h"
#include "datastruct.h"
#include "afficheur.h"
#include "coreLoop.h"
#include "sleep.h"
#include "uart.h"
#include "beep.h"
#include "affichage_ecran.h"

char words[MAXTH][20];

void parseur(char* chaine)
{
	char j=0, k, l, record=0;
	//char used[MAXTH]={0,0,0,0};

	while (chaine[j] != '\0')
	{
		if (chaine[j] == '/')
		{
			record=1;
			k=(chaine[j+1]-0x31);
			//used[k]=1;
			l=0;
			j+=2;
		}
		if (record == 1)
		{
			words[k][l]=chaine[j];
			l++;

			if ((chaine[j+1] == ' ') || (chaine[j+1] == '\0'))
			{
				words[k][l]='\0';
				record=0;
			}
		}
		j++;
	}
}

void decodeur(PLAYER* players, THEME* themes, char* chaine, int vitesse) {

	char k[MAXTH];
	char i=0, j=0, k=0;
	char numTheme, numPlayer;
	char beep=0;
	interrupt_bouton(1);
	while (chaine[i] != '\0')
	{
		if (chaine[i] == '/')
		{
			numTheme=chaine[i+1]-0x31;
			numPlayer=themes[numTheme].idPlayer;
			players[numPlayer].etatMot = 1;
			k[numPlayer] = 0;
			i+=2;
		}

		for(j=0;j<MAXPL;j++) {
			k[j]++;

			if(players[j].etatMot!=WORD_NOTHERE) {
				switch(players[j].etatMot) {
					case WORD_ENTERING:
						if(k[j]==8) {
							players[j].etatMot=WORD_LEAVING;
						}
					break;
					case WORD_LEAVING:
						if(aff_temp[3]==' ') {
							players[j].etatMot=WORD_NOTHERE;
						}
					break;
				}

			}
			else {
				players[j].aJoue=TRY_NOPE;
			}

			if(beep != 0) {
				beep--;
				if(beep == 0) {
					//stoper le buzzer
				}
			}

			if(players[j].aTrouve == FOUND_YES) {
				players[j].aTrouve = FOUND_NOT;
				beep=3;
				//lancer le buzzer
				for(k=0;words[j][k] != '\0';k++) {
					players[j].foundWords[players[j].score][k] = words[j][k];
					k++;
				}
				players[j][k] = '\0'

			}

		}


		push_char(chaine[i++]);
		sleep(vitesse);
	}
	interrupt_bouton(0);
}


void roundLoop(PLAYER* players, THEME* themes, const char phrases[MAXPH][PHLEN], int vitesse) {

	int i=0;
	char j=0;

	while(i<MAXPH)
	{
		parseur(phrases[i]);
		decodeur(players, themes, phrases[i], vitesse);
		for(j=0;j<MAXPL;j++) {
			players[j].etatMot = WORD_NOTHERE;
			players[j].aTrouve = FOUND_NOT;
			players[j].aJoue = TRY_NOPE;
			words[j][0] = '\0';
		}
		i++;
		sleep(66);
	}

}

void jouer(PLAYER* pJoueur)
{
	if(( pJoueur->aJoue==0 ) && ( pJoueur->actif == 1 ))
	{
		switch (pJoueur->etatMot)
		{
			case 0:
				pJoueur->aJoue=2;
				pJoueur->penality++;
			break;
			default:
				pJoueur->aJoue=1;
				pJoueur->aTrouve=FOUND_YES;
				pJoueur->score++;
				affich_ecran(pJoueur);
			break;
		}
	}
}
