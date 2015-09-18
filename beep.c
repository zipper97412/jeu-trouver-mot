#include "stm8s.h"
#include "beep.h"
#include "timer4.h"
#include "ports.h"

/* génère des périodes de 1ms*/
void sleep2(int temps)
{
	int i;
	for (i=0; i<temps; i++)
	{
		TIM3->CNTRH = 0x00;
		TIM3->CNTRL = 0x00;
		TIM3->CR1 |= 0x01;
		while((TIM3->SR1 & TIM3_SR1_UIF) != TIM3_SR1_UIF);
		TIM3->SR1 &= ~TIM4_SR1_UIF; 
		TIM3->CR1 &= ~0x01;
	}
}

void beep(int freq)
{
	int arr;
	arr=(1000000/freq/1.5)-1;
	TIM2->ARRH = arr/256;
	TIM2->ARRL = arr%256;
}

void beepOn(int freq) {
	beep (freq);
	TIM2->CR1 |= (u8)TIM2_CR1_CEN;
	
}

void beepOff(void) {
	TIM2->CR1 &= ~(u8)TIM2_CR1_CEN;
}

void melodie (int freq, int compteur)
{
	TIM2->CR1 &= ~(u8)TIM2_CR1_CEN;
	sleep2(5);
	TIM2->CR1 |= (u8)TIM2_CR1_CEN;
	beep (freq);
	sleep2(compteur);
}

void bruit_decompte(void)
{
	TIM2->CR1 |= (u8)TIM2_CR1_CEN; //Démarre Buzzer
	melodie(cH, 500);
	TIM2->CR1 &= ~(u8)TIM2_CR1_CEN; //Arrête Buzzer
}

void fin_decompte(void)
{
	TIM2->CR1 |= (u8)TIM2_CR1_CEN; //Démarre Buzzer
	melodie(fH, 1000);
	TIM2->CR1 &= ~(u8)TIM2_CR1_CEN; //Arrête Buzzer
}

void marche_imperiale (void)
{
	TIM2->CR1 |= (u8)TIM2_CR1_CEN; //Démarre Buzzer
		melodie(a, 500);
    melodie(a, 500);
    melodie(a, 500);
    melodie(f, 350);
    melodie(cH, 150);  
    melodie(a, 500);
    melodie(f, 350);
    melodie(cH, 150);
    melodie(a, 650);
	  sleep2(150);
    melodie(eH, 500);
    melodie(eH, 500);
    melodie(eH, 500);   
    melodie(fH, 350);
    melodie(cH, 150);
    melodie(gS, 500);
    melodie(f, 350);
    melodie(cH, 150);
    melodie(a, 650);
	  sleep2(150);
    melodie(aH, 500);
    melodie(a, 300);
    melodie(a, 150);
    melodie(aH, 400);
    melodie(gSH, 200);
    melodie(gH, 200); 
    melodie(fSH, 125);
    melodie(fH, 125);    
    melodie(fSH, 250);
    sleep2(250);
    melodie(aS, 250); 
    melodie(dSH, 400); 
    melodie(dH, 200);  
    melodie(cSH, 200);  
		melodie(cH, 125);  
    melodie(b, 125);  
    melodie(cH, 250);  
    sleep2(250);
    melodie(f, 125);  
    melodie(gS, 500);  
    melodie(f, 375);  
    melodie(a, 125);
    melodie(cH, 500);
    melodie(a, 375);  
    melodie(cH, 125);
    melodie(eH, 650);
    melodie(aH, 500);
    melodie(a, 300);
    melodie(a, 150);
    melodie(aH, 400);
    melodie(gSH, 200);
    melodie(gH, 200);
    melodie(fSH, 125);
    melodie(fH, 125);    
    melodie(fSH, 250);
    sleep2(250);
    melodie(aS, 250);  
    melodie(dSH, 400);  
    melodie(dH, 200);  
    melodie(cSH, 200);  
    melodie(cH, 125);  
    melodie(b, 125);  
    melodie(cH, 250);      
    sleep2(250);
    melodie(f, 250);  
    melodie(gS, 500);  
    melodie(f, 375);  
    melodie(cH, 125);
    melodie(a, 500);   
    melodie(f, 375);   
    melodie(cH, 125); 
    melodie(a, 650);   
		
		TIM2->CR1 &= ~(u8)TIM2_CR1_CEN; //Arrête Buzzer
}
