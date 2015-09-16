/* TIMER 4 */
#include "stm8s.h"
#include "stm8s_conf.h"
#include "timer4.h"


/**
\brief cette fonction permet d'initialiser le timer 4
*/
void t4_init(void)
{
}


/**
\brief cette fonction permet de modifier les registres ARR
\param arr la nouvelle valeur à mettre dans les registres
*/
void t4_setARR(u8 arr)
{
	TIM4->ARR = arr;
}

/**
\brief cette fonction permet de modifier la valeur dans le registre du prescalaire
\param pscr la nouvelle valeur a mettre dans le registre
*/
void t4_setPSCR(u8 pscr)
{
	TIM4->PSCR = pscr;
}

/**
\brief cette fonction permet de lancer le comptage
*/
void t4_start(void)
{
	TIM4->CR1=(TIM4->CR1 | TIM4_CR1_CEN);
}

/**
\brief cette fonction permet d'arreter le comptage et de mettre en condition pour repartir
*/
void t4_reset(void)
{
	TIM4->CNTR=0x00;
	TIM4->CR1=(TIM4->CR1 & ~TIM4_CR1_CEN);
	TIM4->SR1=~(TIM4_SR1_UIF) & TIM4->SR1;
}

/**
\brief cette fonction permet de connaitre le contenu actuel du registre CNTR
\return la valeur des registres
*/
u8 t4_getTime(void)
{
	return (TIM4->CNTR);
}

int t4_end(void)
{
	if((TIM4->SR1 & TIM4_SR1_UIF) == TIM4_SR1_UIF)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
\brief cette fonction permet de connaitre le temps écoulé d'un timer en secondes.
\return le temps écoulé en secondes
*/
u8 t4_elapsedTime(void)
{
	int i=0;
	double temps=1.0, fmaster = 2000000.0;
	while (i < TIM4->PSCR)
	{
		temps *= 2.0;
		i++;
	}
	temps *= TIM4->CNTR;
	temps /= fmaster;
}

