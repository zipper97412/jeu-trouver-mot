/* TIMER 3 */
#include "stm8s.h"
#include "stm8s_conf.h"
#include "stm8s_type.h"
#include "timer3.h"

/**
\brief cette fonction permet d'initialiser le timer 3
*/
void t3_init(void)
{
}


/**
\brief cette fonction permet de modifier les registres ARR
\param arr la nouvelle valeur à mettre dans les registres
*/
void t3_setARR(u16 arr)
{
	TIM3->ARRH = (u8)arr & 0xFF00;
	TIM3->ARRL = (u8)arr&0xFF;
}

/**
\brief cette fonction permet de modifier la valeur dans le registre du prescalaire
\param pscr la nouvelle valeur a mettre dans le registre
*/
void t3_setPSCR(u8 pscr)
{
	TIM3->PSCR = pscr;
}


/**
\brief cette fonction permet de lancer le comptage
*/
void t3_start(void)
{
	TIM3->CR1=(TIM3->CR1 | TIM3_CR1_CEN);
}

/**
\brief cette fonction permet d'arreter le comptage et de mettre en condition pour repartir
*/
void t3_reset(void)
{
	TIM3->CNTRH=0x00;
	TIM3->CNTRL=0x00;
	TIM3->CR1 &= ~TIM3_CR1_CEN;
	TIM3->SR1=~(TIM3_SR1_UIF) & TIM3->SR1;
}

int t3_end(void)
{
	if((TIM3->SR1 & TIM3_SR1_UIF) == TIM3_SR1_UIF)
	{
		return 1;
	}
	else
	return 0;
}
/**
\brief cette fonction permet de connaitre le contenu actuel du registre CNTR
\return la valeur des registres
*/
u16 t3_getTime(void)
{
	return(TIM3->CNTRL + TIM3->CNTRH <<8);
}
