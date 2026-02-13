#include "ds18.h"


void ds18_init()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 

	GPIOA->OTYPER |= (1<<0); // PA0 open drain
//	GPIOA->OSPEEDR |= (3<<0); // PA0 high speed 
//	GPIOA->PUPDR |= (1<<0); // PA0 up  

}


uint8_t ds18_search()
{

	uint8_t dt_result;

	PA0_OUTPUT; // пин на выход

	CLEAR_BIT(GPIOA->ODR, 1<<0); // опускаем в 0
		_delay_us(480);

//	SET_BIT(GPIOA->ODR , 1<<0);//подняли линию - отправился 1 

	PA0_INPUT;  // пин на вход
		_delay_us(80); 
	
	dt_result = READ_BIT(GPIOA->IDR , 1<<0); // если пин в нуле то 1 
	_delay_us(500); 

	return dt_result;
}



void ds18_send(uint8_t data)
{
	PA0_OUTPUT;

	for(uint8_t i=0; i<8; i++)
	{


		if (data & (1<<i)!=0)
			{

			PA0_OUTPUT;
		
			CLEAR_BIT(GPIOA->ODR, 1<<0); // down
				_delay_us(1);
			PA0_INPUT; //подняли линию - отправился 1 
				_delay_us(50);

			} 

		else
			{
			
			PA0_OUTPUT;
			CLEAR_BIT(GPIOA->ODR, 1<<0); 
				_delay_us(50);	
			PA0_INPUT; 
			}

	}

}


uint8_t ds18_read()
{

uint8_t data =0;

PA0_INPUT; // read slave

  for(uint8_t i=0; i<8; i++)
	{
		PA0_OUTPUT; 
		CLEAR_BIT(GPIOA->ODR, 1<<0); //down
			_delay_us(2);
		PA0_INPUT; // read slave
		if (READ_BIT(GPIOA->IDR , 1<<0))
		{
			data |= 1<<i;
		}
		_delay_us(60);
	}	 
return data;

}

int16_t ds18_get()
{

int16_t temp;
uint8_t LS_bit;
uint8_t MS_bit;

	if (ds18_search())
	{
		ds18_send(0xCC); //SKIP ROM
		ds18_send(0x44); // CONVERT T
			_delay_ms(750); 

		ds18_search(); //reset
		ds18_send(0xCC); //SKIP ROM
		ds18_send(0xBE); //READ SCRATCHPAD

		LS_bit = ds18_read();
		MS_bit = ds18_read();

	usart1_send_str((char)LS_bit);
	usart1_send_str("\r\n");
	usart1_send_str((char)MS_bit);
	usart1_send_str("\r\n");




		temp = (MS_bit <<8) | LS_bit;

	}
	else
	{
			temp = 0;
	}

return temp;
}

