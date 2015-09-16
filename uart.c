#include "stm8s.h"
#include "uart.h"
#include "stm8s_uart2.h"


void UART_init(void)
{
	UART2->BRR1=0x0D;
	UART2->BRR2=0x00;
	UART2->CR2=UART2->CR2|UART2_CR2_TEN;
	UART2->CR2=UART2->CR2|UART2_CR2_REN;
}

char UART_getchar(void) {
	if ( (UART2->SR & UART2_SR_RXNE) == UART2_SR_RXNE ) {
		return UART2->DR;
	}
	else {
		return EMPTY;
	}
}
u8 UART_putchar(char car){
	if ( (UART2->SR & UART2_SR_TXE) == UART2_SR_TXE ) {
		UART2->DR = car;
		return SUCCESS;
	}
	else {
		return ERROR;
	}
}

u8 UART_putstring(char *chaine) {
	char car;
	int i=0;
	
	while ( (car=chaine[i]) != '\0' ) {
		
		while (UART_putchar(car) == ERROR);
		i++;
	}
		

}
