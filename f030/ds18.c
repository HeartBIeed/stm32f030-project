#include "ds18.h"


void ds18_init()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 

	GPIOA->OTYPER |= 0x01; // PA0 open drain
	GPIOA->OSPEEDR |= (0x10); // PA0 high speed 

}


uint8_t ds18_search()
{

	uint8_t dt_result;

	PA0_OUTPUT; // пин на выход
	CLEAR_BIT(GPIOA->ODR, 0); // опускаем в 0
		_delay_us(500);
	SET_BIT(GPIOA->ODR , 0); // поднимаем в 1
		_delay_us(100);

	PA0_INPUT;  // пин на вход
	if(!(READ_BIT(GPIOA->IDR , 0)))	// если пин в нуле то 1 
		{
			dt_result = 1; // датчик есть
		}
	else{
			dt_result = 0; // датчика нет
		}

	return dt_result;
}



void ds18_send(uint8_t data)
{

	for(uint8_t i=0; i<8; i++)
	{
	PA0_OUTPUT;
	CLEAR_BIT(GPIOA->ODR, 0); 
		_delay_us(2);


	if (data & 0x01) SET_BIT(GPIOA->ODR , 0);//подняли линию - отправился 1 
		_delay_us(70);
	// линию не подняли  - отправился 0 

	data >>=1; // сдвинули под следующий бит
	}

}


uint8_t ds18_read()
{

uint8_t data =0;
uint8_t bit;

  for(uint8_t i=0; i<8; i++)
	{
		PA0_OUTPUT;
		CLEAR_BIT(GPIOA->ODR, 0); 
			_delay_us(2);
		SET_BIT(GPIOA->ODR , 0);
			_delay_us(15);

		PA0_INPUT;
		if(READ_BIT(GPIOA->IDR , 0)) 
			{
			bit = 0x1; 
			}
		else 
			{
			bit = 0x0; 
			}

		_delay_us(45);
		data |= (bit<<i); // запись полученного бита в байт
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
		ds18_send(NOID);
		ds18_send(CONVERT);
			_delay_ms(800); 

		ds18_search();
		ds18_send(NOID);
		ds18_send(READ_DATA);

		LS_bit = ds18_read();
		MS_bit = ds18_read();
		temp = (MS_bit <<8) | LS_bit;

	}
	else
	{
			temp = 0;
	}

return temp;
}

