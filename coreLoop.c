
#include "stm8s.h"
#include "bouton.h"
#include "datastruct.h"
#include "afficheur.h"


void parseur(char phrase[MAXPH], char words[NB_THEME][20]) 
{	
	char j=0, k, l, record=0;
	char used[NB_THEME]={0,0,0,0}; 
	
	while (phrase[j] != '\0') 
	{
		if (phrase[j] == '/') 
		{
			record=1;
			k=chaine[i+1]-0x31;
			used[k]=1;
			l=0;
			j+=2;
		}
		if (record == 1)
		{
			words[k][l]=phrase[j];
			l++;
			
			if ((phrase[j+1] == ' ') || (phrase[j+1] == '\0'))
			{
				words[k][l]='\0';
				record=0;
			}
		}
		j++;
	}
}

void decodeur(PLAYER *players, THEME *themes char chaine[], int vitesse) 
{		
	char k[MAXTHEME];
	char i=0, j=0;
	char numTheme, numPlayer
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
		
		//Si le début du mot est au bout de l'afficheur, on passe dans l'état 2 qui attend un espace
		for(j=0;j<NBJOUEUR;j++)
			if ((k[j]==8) && (players[j].etatMot==WORD_ENTERING))
				players[j].etatMot=WORD_LEAVING;

		//Si le mot est entierrement passé, on dis qu'il n'y a plus de mot a appuyer
		for(j=0;j<NBJOUEUR;j++)
			if ((players[j].etatMot==WORD_LEAVING) && (aff_temp[3]==' '))
				players[j].etatMot=WORD_NOTHERE;

		//On compte le nombre de lettre dans le mot à deviner
		for(j=0;j<NBJOUEUR;j++)
			k[j]++;

		//On fait afficher la nouvelle lettre du mot
		push_char(chaine[i++]);
		
		for(j=0;j<NBJOUEUR;j++)
		{
			if (players[j].etatMot == WORD_NOTHERE)
				players[j].aJoue=TRY_NOPE;
		}
		sleep(vitesse);
	}
	interrupt_bouton(0);
}


void roundLoop(PLAYER players[MAXPL], THEME themes[MAXTH], char phrases[MAXPH][PHLEN], int vitesse) {
	
	int i=0;
	char j=0;
	char words[NBTHEME][20];
	
	while(i<MAXPH)
	{
		parseur(phrases[i], words);
		decodeur(players, themes, phrases[i], vitesse);
		for(j=0;j<3;j++) {
			player[j].etatMot = WORD_NOTHERE;
			player[j].aTrouve = FOUND_NOT;
			player[j].aJoue = TRY_NOPE;
			words[j][0] = '\0';
		}
		i++;
		sleep(66);
	}
	
	
	
}
