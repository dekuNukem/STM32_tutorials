#include "stm32f0xx_hal.h"
#include "delay_us.h"

TIM_HandleTypeDef* us_timer;
volatile uint32_t upper16;

// timer overflow interrupt, happens every 65535us
// simply increment the upper 16 bit
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  upper16++;
}

// initializes timer pointer and start the interrupt
void delay_us_init(TIM_HandleTypeDef* htim_base)
{
	us_timer = htim_base;
	HAL_TIM_Base_Start_IT(us_timer);
}

// combine the upper 16 bit stored in upper16
// with the lower 16 bit in the counter
// to return a 32-bit microsecond timestamp
uint32_t micros(void)
{
  return (upper16 << 16) | (us_timer->Instance->CNT & 0xffff);
}

void delay_us(uint32_t delay)
{
  uint32_t end_time = micros() + delay;
  while(micros() < end_time);
}

