#include "uart.h"

volatile uint8_t uart1_flag = 0;


void UART_init(uint16_t baud)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; //APB bus
//moder 10 - alt 2 bit
	GPIOA->MODER &= ~( 0x3 << (2*2)); //pa2 / clear
	GPIOA->MODER |= ( 0x2 << (2*2)); //pa2 set tx

	GPIOA->MODER &= ~( 0x3 << (3*2)); //pa3 / clear
	GPIOA->MODER |= ( 0x2 << (3*2)); //pa3 set rx
//otyper 0- push-pull 1 bit
	GPIOA->OTYPER &= ~((1<<2)|(1<<3)); //pa2 pa3 to  0
//speed 10 high 2 bit
	GPIOA->OSPEEDR |= ((0x2<<(2*2))|(0x2<<(3*2))); //pa2 pa3 to  0b10

	GPIOA->AFR[0] &= ~((0xF<<(2*4))|(0xF<<(3*4))); //0b001 usart tx rx enable mode
	GPIOA->AFR[0] |= ((0x1<<(2*4))|(0x1<<(3*4)));  //0b001/ 4 bit on 1 pin

	USART1->CR1 = 0;
	USART1->CR2 = 0;
	USART1->CR3 = 0;
		
	USART1->BRR = FCPU/baud; 

	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE; //tx rx usart enable

}

void usart1_send_byte(char tx_data)
	{
		while ((USART1->ISR & USART_ISR_TXE) == 0);
	 	USART1->TDR = tx_data;
	}



void usart1_send_str(char *str) // TX string
	{
		while (*str) 
		{

		usart1_send_byte((uint8_t)*str++);
		
		}

	}



uint8_t usart1_recieve_byte()
	{
//		while ((USART1->ISR & USART_ISR_RXNE) == 0);
		if (USART1->ISR & USART_ISR_RXNE) 
			{
				return (uint8_t)USART1->RDR;
			}
return 0;
	}









