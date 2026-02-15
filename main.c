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

	SystemClock_HSI_8MHz();
	SysTick_init();

	I2C_init( );
	UART_init(9600);

	GPIO();
	usart1_send_str("UART EN");

//uint16_t temp_ds = 0;
char data_ds[32];
		PA0_INPUT; 

 while( 1 )
	{

		if (READ_BIT(GPIOA->IDR ,1<<0)) 	usart1_send_str("1");
		usart1_send_str("0");
		_delay_ms(100);

/*
	sprintf(data_ds,"SRCH = %u \n\r",ds18_search());
	usart1_send_str(data_ds);
		_delay_ms(10);



	sprintf(data_ds,"DS = %u \n\r",ds18_get());
	usart1_send_str(data_ds);
		_delay_ms(500);
*/


	}
}
