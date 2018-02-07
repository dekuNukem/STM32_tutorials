# `HAL_UART_Transmit()` function Details

This is the blocking function for sending data via UART. We're mostly using it for `printf()` so you don't have to worry about the details, but if you do, its prototype is:

`HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);`

First argument is a pointer to an UART device handle. Device handles are structs that hold configuration information. They appear as you enable peripherals and are always found in `main.c` under `/* Private variables --------------*/`. Most of HAL peripheral functions need a pointer to a device handle.

Second argument is a pointer to an `uint8_t` array that contains the data you want to send.

Third argument is an `uint16_t` number that specifies how many bytes to send from the above array.

Last argument is a timeout in milliseconds. If it is exceeded while operation is still ongoing, the function will abort and return a timeout error. Don't set it too small, 100ms is plenty in this case.

A simple usage is:

```
uint8_t* msg = "hello world\n";
HAL_UART_Transmit(&huart1, msg, 12, 100);
```

In this case, the function sends 12 bytes of data in array `msg` through UART1.

If you want to use `strlen()` and such, don't forget to `#include <string.h>` between the `/* USER CODE Includes */` comment blocks.

Again, this function is mostly used as a part of `printf`, so don't worry about using it on its own for now.