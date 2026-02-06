#include "main.h"

void AHT_to_uart()		
{
	uint8_t init_aht20[3] = {0xBE,0x08,0x00};
	uint8_t trig[3] = {0xAC, 0x33, 0x00};
	uint8_t buffer[6];
	char string[32];


	if (I2C_check_address(0x38))
		{
			usart1_send_str("AHT EN\n\r");
		}

	else {
			usart1_send_str("I2C none 0x38\n\r");
		}

	I2C_write_byte(0x38,init_aht20,3);
			_delay_ms(50);

	I2C_write_byte(0x38,trig,3);
			_delay_ms(100);

	I2C_read_byte(0x38,buffer,6);

	uint32_t raw_H = (buffer[1] <<12) | (buffer[2] << 8) | (buffer[3]>>4);
	uint32_t raw_T = ((buffer[3] & 0x0F) <<16) | (buffer[4] << 8) | buffer[5];

	uint32_t Humi = raw_H * 100 / 1048576; //1048576 2^20
	uint32_t Temp = raw_T * 200 / 1048576 - 50;

	sprintf(string,"H = %lu \n\r",Humi);
	usart1_send_str(string);

	sprintf(string,"T = %lu \n\r",Temp);
	usart1_send_str(string);

	string[0] = '\0';
}


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

	GPIOA->ODR |= (1 << 5); // PA5 en relay
	usart1_send_str("UART EN");

int16_t temp_ds = 0;
char data_ds[32];

 while( 1 )
	{


	AHT_to_uart();
	_delay_ms(500);

	sprintf(data_ds,"SRCH = %u \n\r",ds18_search());
	usart1_send_str(data_ds);
_delay_ms(500);

	temp_ds = ds18_get() ;
	sprintf(data_ds,"DS = %u \n\r",temp_ds);
	usart1_send_str(data_ds);

	_delay_ms(500);


	}
}

