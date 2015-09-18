#include "sleep.h"
#include "stm8s.h"

#define VIT1 12
#define VIT2 11
#define VIT3 10
#define VIT4 9
#define VIT5 8
#define VIT6 7
#define VIT7 6
#define VIT8 1

void elem_sleep(void) {
	TIM4->CNTR=0x00;
	TIM4->CR1=(TIM4->CR1 | TIM4_CR1_CEN);

	while ((TIM4->SR1 & TIM4_SR1_UIF) != TIM4_SR1_UIF);
	TIM4->SR1=~(TIM4_SR1_UIF) & TIM4->SR1;
	TIM4->CR1=(TIM4->CR1 & ~TIM4_CR1_CEN);
}

void sleep(int potar) 
{
	int i;
	switch(potar) 
	{
		case 1: 
			for(i=0;i<VIT1;i++) 
			{
				elem_sleep();
			}
		break;
		case 2: 
			for(i=0;i<VIT2;i++) 
			{
				elem_sleep();
			}
		break;
		case 3: 
			for(i=0;i<VIT3;i++) 
			{
				elem_sleep();
			}
		break;
		case 4: 
			for(i=0;i<VIT4;i++) 
			{
				elem_sleep();
			}
		break;
		case 5: 
			for(i=0;i<VIT5;i++) 
			{
				elem_sleep();
			}
		break;
		case 6: 
			for(i=0;i<VIT6;i++) 
			{
				elem_sleep();
			}
		break;
		case 7: 
			for(i=0;i<VIT7;i++) 
			{
				elem_sleep();
			}
		break;
		case 8: 
			for(i=0;i<VIT8;i++) 
			{
				elem_sleep();
			}
		break;
		default:
			for(i=0;i<potar;i++)
			{
				elem_sleep();
			}
	}
}