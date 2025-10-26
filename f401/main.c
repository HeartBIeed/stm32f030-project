#include "main.h"


void gpio_init()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; 
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; 

//	GPIOA->MODER |= ( 0x01 << (5*2)); //pa5 / output 0x01
//	GPIOA->MODER |= ( 0x01 << (6*2)); //6
//	GPIOA->MODER |= ( 0x01 << (7*2)); //7

GPIOC->MODER |= ( 0x01 << (13*2)); //PC13 / output 01

//	GPIOB->MODER &= ~( 0xFF << (1*2)); //pb1 / input 0x00
//	GPIOB->PUPDR |= ( 0x01 << (1*2)); //pb1 / up 01

//	GPIOB->MODER |= ( 0x01 << (3*2)); //pb3 / output 01
}



int main(void)
{
//	for (volatile int i=0; i<100000; i++);

	PLL_enable();

	SysTick_init();
	DWT_init();

//	UART_init(9600u);
	gpio_init();

//		CLEAR_BIT(GPIOC->ODR, (1 << 13));
GPIOC->BSRR = (1 << (13 + 16));
			_delay_ms(5000);


 while( 1 )
	{
		SET_BIT(GPIOC->ODR, (1 << 13));
		_delay_ms(5000);
		CLEAR_BIT(GPIOC->ODR, (1 << 13));
		_delay_ms(5000);
/*
uint8_t data = usart1_recieve_byte();		

usart1_ptr_str("UABC1");


		if ( data == '6')
		{

			GPIOA->ODR |= (1 << 6);
		
		}

		else if (data == '7')
		{

			GPIOA->ODR |= (1 << 7);
		
		}		

		else if (data == 'S')
		{
		usart1_ptr_str("string");
		
		}

		else
		{
		usart1_echo();
		}

*/
	}
}

