#include "main.h"



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


// ------- init AHT20 ---------
char init_aht20[3] = {0xBE,0x08,0x00};
 I2C_write_byte(0x38,init_aht20,3);

char trig[3] = {0xAC, 0x33, 0x00};

//---------------------------
char buffer[6];
		_delay_ms(100);


 while( 1 )
	{

if (I2C_check_address(0x38))
	{
		usart1_send_str("AHT EN\n\r");
	}

else {
		usart1_send_str("I2C none 0x38\n\r");
	}

 I2C_write_byte(0x38,trig,3);
		_delay_ms(100);

I2C_read_byte(0x38,buffer,6);

uint32_t raw_T = 
(((uint32_t)buffer[3] & 0x0F) << 16 )|
((uint32_t)buffer[4] << 8) |
((uint32_t)buffer[5]);

uint32_t Temp = raw_T * 200/2 ^20 - 50;

usart1_send_str((char)Temp);


		_delay_ms(500);




	}
}

