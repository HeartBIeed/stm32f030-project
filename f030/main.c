#include "main.h"


int main(void)
{

	SystemClock_HSE_8MHz();
	SysTick_init();
	



	UART_init(9600);

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 

//						 PA output(01)

	GPIOA->MODER |= ( 0x01 << (5*2)); // 5 / 01
	GPIOA->MODER |= ( 0x01 << (6*2)); // 6
	GPIOA->MODER |= ( 0x01 << (7*2)); // 7
	GPIOA->MODER |= ( 0x01 << (15*2)); // 15 

//						 PB input 00

	GPIOB->MODER &= ~( 3 << (1*2));// 1 
	GPIOB->PUPDR |= ( 1 << (1*2)); //1 / up 01

//  output 01 input 00



	GPIOA->ODR |= (1 << 5); // PA5 en relay

	usart1_ptr_str("UART EN");

	char data[16];

 while( 1 )
	{

	dht_write_data(data);
	
	_delay_ms(3000);
	usart1_ptr_str(data);
	usart1_ptr_str("\r\n");

	}
}

