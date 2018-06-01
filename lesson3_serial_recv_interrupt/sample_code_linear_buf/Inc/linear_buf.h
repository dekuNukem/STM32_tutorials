#include "stm32f0xx_hal.h"

#ifndef LINEAR_BUF_H
#define LINEAR_BUF_H

#define LB_SIZE 256

typedef struct
{
	int16_t curr_index;
	char buf[LB_SIZE];
} linear_buf;

#endif

