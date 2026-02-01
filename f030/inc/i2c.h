#ifndef I2C_H_
#define I2C_H_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

#define PB6 6
#define PB7 7

#define I2C_H_



void I2C_init( );
void I2C_start(int addr,int nbytes);
void I2C_stop( );
int I2C_send_byte(char data,int addr);


#endif /* I2C_H_ */
