#include "prejeu.h"
#include "stm8s.h"
#include "afficheur.h"
#include "sleep.h"
#include "bouton.h"

int nb_appui(void)
{
	int nbBoutons=0;
	if(Etat_BP01()==0)
	{
		nbBoutons++;
	}
	if(Etat_BP02()==0)
	{
		nbBoutons++;
	}
	if(Etat_BP03()==0)
	{
		nbBoutons++;
	}
	if(Etat_BP04()==0)
	{
		nbBoutons++;
	}
}

	
void decompte(void)
{
	char temp[]="    5   ";
	clear();
	printtab(temp); sleep(66);
	temp[4]='4';
	printtab(temp); sleep(66);
	temp[4]='3';
	printtab(temp); sleep(66);
	temp[4]='2';
	printtab(temp); sleep(66);
	temp[4]= '1';
	printtab(temp); sleep(66);
	temp[4]= ' ';
	printtab(temp); sleep(66);
	
}	