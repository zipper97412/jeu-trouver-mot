#include "stm8s.h"
#include "bouton.h"
#define ACTIF 1
#define INACTIF 0

char Etat_BP01(void)
{
	if(((GPIOC->IDR)&(GPIO_PIN_1))==GPIO_PIN_1)
			return(INACTIF);
	else
			return(ACTIF);
}

char Etat_BP02(void)
{
	if(((GPIOC->IDR)&(GPIO_PIN_2))==GPIO_PIN_2)
			return(INACTIF);
	else
			return(ACTIF);
}

char Etat_BP03(void)
{
	if(((GPIOC->IDR)&(GPIO_PIN_3))==GPIO_PIN_3)
			return(INACTIF);
	else
			return(ACTIF);
}

char Etat_BP04(void)
{
	if(((GPIOC->IDR)&(GPIO_PIN_4))==GPIO_PIN_4)
			return(0);
	else
			return(1);
}

char interrupt_bouton(char etat_bp)
{
	if (etat_bp==1)
		GPIOC->CR2 = 0x0E;
	else
		GPIOC->CR2=0x00;
}