#ifndef RTC_H_
#define RTC_H_


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void RTC_init();
void RTC_set_time(uint8_t h,uint8_t m);
void RTC_get_time(uint8_t *hour,uint8_t *min);


#endif /* RTC_H_ */
