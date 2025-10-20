#include "main.h"


int main(void)
{
	SystemClock_HSE_8MHz();

	UART_init(9600u);

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 

	GPIOA->MODER |= ( 0x01 << (5*2)); //pa5 / output 01
	GPIOA->MODER |= ( 0x01 << (6*2)); //6
	GPIOA->MODER |= ( 0x01 << (7*2)); //7


	GPIOB->MODER &= ~( 0xFF << (1*2)); //pb1 / input 00
	GPIOB->MODER |= ( 0x01 << (3*2)); //pb3 / output 01
	GPIOB->PUPDR |= ( 0x01 << (1*2)); //pb1 / up 01

	GPIOA->ODR |= (1 << 5);

		usart1_ptr_str("HELLO");

 while( 1 )
	{


		usart1_ptr_str("1234ABCD");




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


	}
}

