#include "main.h"

void I2C_scan()
	{
	int addr;

	for (addr = 0x08; addr < 0x77; addr++)
		{
			if (I2C_check_address(addr)) usart1_send_str("GET \n\r");

		}

	}

int main(void)
{

	SystemClock_HSE_8MHz();
	SysTick_init();
	


	I2C_init( );
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

	usart1_send_str("UART EN");

		_delay_ms(1000);

 while( 1 )
	{

//	I2C_scan();
	
	if (I2C_check_address(0x38)) 
		{
			usart1_send_str("GET 38\n\r");
		}

	else {
			usart1_send_str("I2C none 38\n\r");
		}

		_delay_ms(500);

	if (I2C_check_address(0x77)) 
		{
			usart1_send_str("GET 77 \n\r");
		}

	else {
			usart1_send_str("I2C none 77\n\r");
		}


		_delay_ms(500);

	}
}

