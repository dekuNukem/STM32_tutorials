#include "my_tasks.h"
#include "cmsis_os.h"

void StartDefaultTask(void const * argument)
{
  for(;;)
  {
  	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
    osDelay(1000);
  }
}

void StartTask02(void const * argument)
{
  for(;;)
  {
  	printf("serial task\n");
    osDelay(250);
  }
}
