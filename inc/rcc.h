#ifndef RCC_H_
#define RCC_H_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void SystemClock_HSE_8MHz(void);
void SystemClock_HSI_8MHz(void);
void PLL_enable();



#endif /* RCC_H_ */
