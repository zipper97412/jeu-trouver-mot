#include "stm8s.h"
#include "stm8s_conf.h"
#include "ports.h"

void init_ports(void)
{
	GPIOA->DDR = 0xFF;
	GPIOA->CR1 = 0x00;
	
	GPIOB->DDR = PORT_B_DIRECTION;
	GPIOB->CR1 = PORT_B_TECHNO_LIGNES;

	GPIOC->DDR = PORT_C_DIRECTION;
	GPIOC->CR1 = PORT_C_TECHNO_LIGNES;

	GPIOD->DDR |= PORT_D_DIRECTION; 
	GPIOD->CR1 = PORT_D_TECHNO_LIGNES; // pull up pour ligne 7

	GPIOE->DDR |= PORT_E_DIRECTION; 
	GPIOE->CR1 = PORT_E_TECHNO_LIGNES;

	GPIOG->DDR |= PORT_G_DIRECTION; 
	GPIOG->CR1 = PORT_G_TECHNO_LIGNES;  // pour signaux A0 et A1

	GPIOD->ODR = HDLX_NBL;
	GPIOE->ODR = HDLX_NWR1 + HDLX_NWR2; // 2 signaux /WR au repos
	
		EXTI->CR1 = 0x10;
	_asm("rim\n");
	
}

  void Init_Timer2(void)
 {
	TIM2->PSCR = 0x02;
	TIM2->CCER1 = 0x03;
	TIM2->CCMR1 = 0x70;
	TIM2->CCR1H = 0x01;
	TIM2->CCR1L = 0xF4;
	TIM2->CCMR1 |= 0x08;
	TIM2->CR1 |= TIM2_CR1_ARPE;
 }
 
   void Init_Timer4(void)
 {
	TIM4-> PSCR = 0x03;
	TIM4-> ARR = 0xF9; 
 }