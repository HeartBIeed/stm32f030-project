#include "main.h"


int main(void)
{

	SystemClock_HSE_8MHz();
	SysTick_init();
	SysTick_Handler();



	UART_init(9600u);

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 

//						 PA output(01)

	GPIOA->MODER |= ( 0x01 << (5*2)); // 5 / 01
	GPIOA->MODER |= ( 0x01 << (6*2)); // 6
	GPIOA->MODER |= ( 0x01 << (7*2)); // 7
	GPIOA->MODER |= ( 0x01 << (15*2)); // 15 

//						 PB input 00

	GPIOB->MODER &= ~( 0xFF << (1*2));// 1 
	GPIOB->MODER |= ( 0x01 << (3*2)); // 3
	GPIOB->PUPDR |= ( 0x01 << (1*2)); //1 / up 01

//  output 01 input 00



	GPIOA->ODR |= (1 << 5); // PA5 en relay

	usart1_ptr_str("UART EN");


 while( 1 )
	{

/*
	GPIOA->ODR |= (1 << 5);
	_delay_ms(2000);


	GPIOA->ODR &= ~(1 << 5);
	_delay_ms(2000);

*/

uint8_t data = usart1_recieve_byte();		

	if ( data == '6') 
		{
			GPIOA->ODR |= (1 << 6);
		}

	else if (data == '7') 
		{
			GPIOA->ODR |= (1 << 7);
		}

	else if (data == 's') 
		{
			usart1_ptr_str("string");
		}

	else
		{
		usart1_echo();
		}

/*-----------------------------------------------------------------------------
		if ((GPIOB->IDR & (1<<1))==0)
			{
			GPIOA->ODR |= (1 << 15);
			GPIOB->ODR &= ~(1 << 3);
		usart1_ptr_str("yellow");


			}
		else 
			{
			GPIOA->ODR &= ~(1 << 15);
			GPIOB->ODR |= (1 << 3);
		usart1_ptr_str("Green");

			}

--------------------------------------------------------
*/
	}
}

