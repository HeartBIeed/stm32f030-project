#ifndef DS18_H_
#define DS18_H_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

#define NOID 0xCC //Пропустить идентификацию
#define CONVERT 0x44 //Старт измерения температуры
#define READ_DATA 0xBE //Передача байтов ведущему


#define PA0_INPUT 	(GPIOA->MODER &= ~(0x03)) // PA0 input 
#define PA0_OUTPUT 	(GPIOA->MODER = (GPIOA->MODER & ~(0x03))| 0x01) // PA0 output 

void ds18_init();
uint8_t ds18_search();
uint8_t ds18_read();
void ds18_send(uint8_t data);
uint32_t ds18_get();


#endif /* DS18_H_ */
