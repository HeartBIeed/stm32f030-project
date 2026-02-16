#include "ds18.h"


void ds18_init()
	{
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN; 

		GPIOA->OTYPER |= (1<<0); // PA0 open drain
		GPIOA->OSPEEDR |= (3<<0); // PA0 high speed 

	}


uint8_t ds18_search()
	{

	uint8_t dt_result;
	uint8_t presence;
	uint8_t bus_high;

	PA0_OUTPUT; 							// пин на выход

		CLEAR_BIT(GPIOA->ODR, 1<<0); 			// опускаем в 0
			_delay_us(480); 						// */20

	PA0_INPUT; 								 // пин на вход
			
			_delay_us(40); 						// ждем время после отпуска шины
		

		if (READ_BIT(GPIOA->IDR ,1<<0)==0) 		// ответ датчика через 40 мкс
			{
				presence = 1;
			} else {
				presence = 0;
			}

			_delay_us(250); 						// ждем время отпуска шины датчиком
		
		if (READ_BIT(GPIOA->IDR ,1<<0)==1) 		// проверка возврата в 1 через 250 мкс
			{
				bus_high = 1;
			} else {
				bus_high = 0;
			}
		
		if ((presence==1) & (bus_high==1) )	// совпадение условий 1 и 2
			{
				dt_result = 1;
			} else {
				dt_result = 0;
			}


	return dt_result; 							// результат - отработка датчика
	}



void ds18_send(uint8_t data)
	{
	PA0_OUTPUT;

	for(uint8_t i=0; i<8; i++)
		{

		if (data & (1<<i))
			{

			PA0_OUTPUT;
				CLEAR_BIT(GPIOA->ODR, 1<<0); // down
				
				__NOP();__NOP();__NOP();__NOP();

			PA0_INPUT; //подняли линию - отправился 1 
				_delay_us(40);
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
		PA0_INPUT;

		for(uint8_t i=0; i<8; i++)
			{

			PA0_OUTPUT; 
			CLEAR_BIT(GPIOA->ODR, 1<<0); //down
			
			__NOP();__NOP();__NOP();__NOP();

						PA0_INPUT; 

			_delay_us(10); // 20 мкс

			if (READ_BIT(GPIOA->IDR ,1<<0)==1) 
				{	
					data |= 1<<i; // 1
					_delay_us(25); // 40 мкс

				} else {

					_delay_us(40);

				}

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

			temp = (MS_bit <<8) | LS_bit;

		}
		else
		{
				temp = 0;
		}

	return temp;
	}

