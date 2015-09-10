#include "stm8s.h"
#include "potentiometre.h"
#include "stm8s_adc1.h"
#include "sleep.h"
#include "bouton.h"
#include "afficheur.h"
#include "uart.h"

u8 aff_tempb[8];

char potentiometre (void)
{
	u8	high = 0, low = 0, tempA = 0, tempB = 0;
	u16 mes = 0;
	char i = 0; 	char n=0 ;
	char text[] = "Les phrases defileront a cette vitesse.  ";
		ADC1->CSR |= ADC1_CHANNEL_9;
	ADC1->CR2 |= ADC1_ALIGN_RIGHT;	
	ADC1->CR1 |= 0x01;

	while ( Etat_BP04() != 0 )
		{
		ADC1->CR1 |= 0x01;
		while ( (ADC1->CSR & ADC1_IT_EOC) != ADC1_IT_EOC ) ;
		ADC1->CSR &= ~ADC1_IT_EOC;
		tempA = ADC1->DRL ;	
		low = tempA;
		high = ADC1->DRH ;
		mes = ((u8) high << 8) | low;
		
		//Allumage des LED
		if (mes < 0x0050) 
		{
			GPIOA->ODR = 0xF7 ;
			n = 1;
		}
		if (mes > 0x0050 && mes < 0x0125 ) 
		{
			GPIOA->ODR = 0xE7 ;
			n = 2;
		}
		if (mes > 0x0125 && mes < 0x0200 )
		{
			GPIOA->ODR = 0xC7 ;
			n = 3;
		}
		if (mes > 0x0200)
		{
			GPIOA->ODR = 0x87 ;
			n = 4;
		}
		
		//Defilement de la phrase de test en boucle
		if ( text[i] == '\0' ) i=0;
		push_char(text[i++]);
		sleep(n);
	}
	clear();
	UART_putstring("\r\nLa vitesse selectionnee est "); 	
	while((UART_putchar(n+0x30)==1));
	return n;
}
