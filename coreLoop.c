#include "stm8s.h"
#include "bouton.h"
#include "datastruct.h"
#include "afficheur.h"
#include "coreLoop.h"
#include "sleep.h"
#include "uart.h"
#include "beep.h"
#include "affichage_ecran.h"
#include "leds.h"
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
	char i=0, j=0, l=0;
	char numTheme, numPlayer;
	char winFeedbackLed[MAXPL];
	char winFeedbackBeep[MAXPL];
	char lostFeedbackLed[MAXPL];
	interrupt_bouton(1);
	ledInit();
	
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


			feedbackManager(winFeedbackLed, winFeedbackBeep, lostFeedbackLed, j);
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
				if(players[j].aJoue == TRY_LOST) {
					lostFeedbackLed[j]=FEEDBACK_LED;
					ledOn(j+4);
					
				}
				players[j].aJoue=TRY_NOPE;
				
			}
			
			if(players[j].aTrouve == FOUND_YES) {
				players[j].aTrouve = FOUND_NOT;
				winFeedbackLed[j]=FEEDBACK_LED;
				winFeedbackBeep[j]=FEEDBACK_BUZZER;
				beepOn(fH);
				ledOn(j);
			}
		}


		push_char(chaine[i++]);
		sleep(vitesse);
	}
	interrupt_bouton(0);
}

void feedbackManager(char* winFeedbackLed, char* winFeedbackBeep, char* lostFeedbackLed, char j) {
	
	if((winFeedbackLed[j]) != 0) {
		(winFeedbackLed[j])--;
		if((winFeedbackLed[j]) == 0) {
			ledOff(j);
		}
	}
	if((winFeedbackBeep[j]) != 0) {
		(winFeedbackBeep[j])--;
		if((winFeedbackBeep[j]) == 0) {
			beepOff();
		}
	}
	if((lostFeedbackLed[j]) != 0) {
		(lostFeedbackLed[j])--;
		if((lostFeedbackLed[j]) == 0) {
			ledOff(j+4);
		}
	}
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
	if(( pJoueur->aJoue==TRY_NOPE ) && ( pJoueur->actif == 1 ))
	{
		switch (pJoueur->etatMot)
		{
			case WORD_NOTHERE:
				pJoueur->aJoue=TRY_LOST;
				pJoueur->penality++;
			break;
			default:
				pJoueur->aJoue=TRY_WON;
				pJoueur->aTrouve=FOUND_YES;
				pJoueur->score++;
				affich_ecran(pJoueur);
				
			break;
		}
	}
}
