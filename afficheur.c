#include "afficheur.h"
#include "stm8s.h"
#include "stm8s_conf.h"
#include "ports.h"
u8 aff_temp[8];

//Fonction qui affiche le contenu d'un tableau sur les afficheurs
void disp() 
{
	HDLX2(aff_temp);
	HDLX1((aff_temp+4));
}
void printtab(char tab[])
{
	int i=0;
	for(i=0;i<8;i++)
	{
		aff_temp[i]=(u8)tab[i];
	}
	disp();
}
//Fonction qui efface les afficheurs
void clear(void)
{
	int i=0;
	for (i=0;i<8;i++)
		aff_temp[i]=' ';
	disp();
}

//Fonction qui permet de décaler le texte et d'inserer une lettre à gauche
void push_char(u8 c) 
{
	int i=0;
	for(i=0;i<7;i++) 
		aff_temp[i]=aff_temp[i+1];
	aff_temp[7]=c;
	disp();
}

//Fonctions qui gère l'afficheur (les 2 HDLX)

void HDLX1_digit(u8 numero, u8 caractere)
{
GPIOB->ODR = caractere + 0x80; // MSB = 1 pour caractere ASCII
GPIOG->ODR = numero ;   //  numero digit
GPIOE->ODR = GPIOE->ODR & ~HDLX_NWR1; // activation /WR1
GPIOE->ODR = GPIOE->ODR | HDLX_NWR1; // deactivation /WR1
}

void HDLX2_digit(u8 numero, u8 caractere)
{
GPIOB->ODR = caractere + 0x80; // MSB = 1 pour caractere ASCII
GPIOG->ODR = numero ;   //  numero digit
GPIOE->ODR = GPIOE->ODR & ~HDLX_NWR2; // activation /WR2
GPIOE->ODR = GPIOE->ODR | HDLX_NWR2; // deactivation /WR2
}

void HDLX1(u8* chaine)
{
u8 *pointeur;
s8 numero; // numero digit
pointeur = chaine;
for ( numero = 3 ; numero > -1 ; numero -- )
  {
   HDLX1_digit(numero, *pointeur);
   pointeur ++;
  }
}

void HDLX2(u8* chaine)
{
u8 *pointeur;
s8 numero; // numero digit
pointeur = chaine;
for ( numero = 3 ; numero > -1 ; numero -- )
	{
	HDLX2_digit(numero, *pointeur);
	pointeur ++;
	}
}