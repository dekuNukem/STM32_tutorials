#ifndef LINEAR_BUF_H
#define LINEAR_BUF_H

#include "stm32f0xx_hal.h"
#define LB_SIZE 256

typedef struct
{
	int16_t curr_index;
	char buf[LB_SIZE];
} linear_buf;

void linear_buf_reset(linear_buf *lb);
void linear_buf_add(linear_buf *lb, char c);
uint8_t linear_buf_ready(linear_buf *lb);

#endif

