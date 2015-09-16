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
	char i=0, j=0;
	char numTheme, numPlayer;
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
		
		//Si le debut du mot est au bout de l'afficheur, on passe dans l'etat 2 qui attend un espace
		for(j=0;j<MAXPL;j++)
			if ((k[j]==8) && (players[j].etatMot==WORD_ENTERING))
				players[j].etatMot=WORD_LEAVING;

		//Si le mot est entierrement passe, on dis qu'il n'y a plus de mot a appuyer
		for(j=0;j<MAXPL;j++)
			if ((players[j].etatMot==WORD_LEAVING) && (aff_temp[3]==' '))
				players[j].etatMot=WORD_NOTHERE;

		//On compte le nombre de lettre dans le mot a  deviner
		for(j=0;j<MAXPL;j++)
			k[j]++;
		
		
		//On fait afficher la nouvelle lettre du mot
		push_char(chaine[i++]);
		
		for(j=0;j<MAXPL;j++)
		{
			if (players[j].etatMot == WORD_NOTHERE)
				players[j].aJoue=TRY_NOPE;
		}
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
				pJoueur->aTrouve=1;
				pJoueur->score++;
				affich_ecran(pJoueur);
			break;
		}
	}
}
