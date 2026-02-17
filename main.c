#include "main.h"

void GPIO()
	{
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 
		RCC->AHBENR |= RCC_AHBENR_GPIOBEN; 

		GPIOA->MODER |= ( 0x01 << (5*2)); // 5 pin/ 01
		// PA output 0x10

		GPIOB->MODER &= ~( 3 << (1*2));// 1 pin
		GPIOB->PUPDR |= ( 1 << (1*2)); //1 pin / up 01
		// PB input 0x00

	}

int main(void)
{

	SystemClock_HSE_8MHz();
	SysTick_init();

	I2C_init( );
	UART_init(9600);

	GPIO();
	usart1_send_str("UART EN");

char data_ds[32];

 while( 1 )
	{


	sprintf(data_ds,"SRCH = %u \n\r",ds18_search());
	usart1_send_str(data_ds);
		_delay_ms(10);

	sprintf(data_ds,"DS = %u \n\r",ds18_get() /16 );
	usart1_send_str(data_ds);
		_delay_ms(500);

	}
}
