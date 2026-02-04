#ifndef I2C_H_
#define I2C_H_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void I2C_init( );
int I2C_check_address(int addr);
void I2C_read_byte(int addr,uint8_t* data,int len);
void I2C_write_byte(int addr,uint8_t* data,int nbytes);
void I2C_scan();

#define TIMEOUT 1000
#define PB6 6 
#define PB7 7

#endif /* I2C_H_ */
