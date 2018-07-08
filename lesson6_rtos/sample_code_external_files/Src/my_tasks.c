#include "my_tasks.h"
#include "cmsis_os.h"

void StartLEDtask(void const * argument)
{
  for(;;)
  {
  	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
    osDelay(200);
  }
}

void StartUARTtask(void const * argument)
{
  for(;;)
  {
  	printf("This is UART task\n");
    osDelay(500);
  }
}
