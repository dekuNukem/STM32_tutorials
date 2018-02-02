# Lesson 1: UART and Hello World

Previous lesson: [A Complete Walkthrough of Board Detail, Software Setup, and Blinking LED](../lesson0_intro_blinkLED/README.md)

In this lesson we'll get UART transmit working, then set up `printf()` to print our `hello world` over serial.

I don't think I need to elaborate on how important UARTs are in embedded systems, so let's get right to it!

## UART setup in STM32CubeMX

We will be reusing the entire project from the last lesson, so just make a new copy of the project folder. After that, double click and open the `.ioc` file.

![Alt text](resources/ioc.png)

Which will take you back to the pin view page:

![Alt text](resources/cubehome.png)

This time we expand `USART1` and select `Asynchronous` mode. Two more pins are now in use. `PA2` is TX, while `PA3` is RX.

![Alt text](resources/cubeuart.png)

Next we go to the configuration page. Click the newly appeared button to adjust a few settings.

![Alt text](resources/cubeconfig.png)

The only thing that actually needs changing is the baud rate, you can set it to whatever you want but I like 115200bps.

While you're here take a look at the `Advanced Features`, so many options! It even has TX/RX pin swapping for when you forget to cross the wires! What a world we're living in.

![Alt text](resources/cubesetup.png)

That's it for the CubeMX! Make sure the Keil MDK is closed, and regenerate the code: 

![Alt text](resources/cubecode.png)

The best practice to **keep Keil MDK closed while regenerating the code in STM32CubeMX**, this keep things consistent and less likely to corrupt the project files. After it's done, click `Open Project` button to launch Keil MDK.

![Alt text](resources/cubecode2.png)

## Printing "Hello World"

Now we're ready to code our "Hello World" program. Remember what to do when encountering a new peripheral? Yep, we go and see what functions we can use in the HAL library files.

Looking at the [stm32f0xx_hal_uart.h](sample_code/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_uart.h), we find the following functions:

```
/* IO operation functions *****************************************************/
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_DMAPause(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAResume(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAStop(UART_HandleTypeDef *huart);
```

That's a lot of choices, but we can break it down to 3 groups: blocking, IT and DMA.

In fact, in HAL you can use most of the I/O peripherals in those 3 ways:

### Blocking Mode:

You ask the peripheral to do something, and then just wait for it to finish.

Their HAL functions don't usually have suffixes, in this case it's simply called `HAL_UART_Transmit()`.

#### Advantages

It's simple and straightforward to use. In fact this is what we're using in this lesson.

#### Drawbacks

Since you can't do anything else while waiting, you're wasting valuable CPU time doing nothing. And as a result the performance takes a hit. And if the peripheral is slow, the waiting time can be significant.

### Interrupt Mode:

You ask the peripheral to do something, and an interrupt will be raised when the task is finished.

Their HAL functions usually ends in `_IT`, in this case it's called `HAL_UART_Transmit_IT()`.

#### Advantages

There is no need for waiting, the function returns immediately and you can do something else while the peripheral is working on your task. This improves the respond time and general performance.

#### Drawbacks

It's slightly more complicated to set up, and can become rather chaotic as the complexity of your program picks up. There are also potential synchronization problems if you're not careful with how the data is accessed.

### DMA Mode:

DMA stands for Direct Memory Access, in short in this mode data is transfered between the memory and peripheral directly without going through CPU at all. This has the best performance and is suitable for very high data transfer rates.

#### Advantages

Since the data is moved directly from memory to the peripheral, this has the fastest transfer rate. And at the same time this frees up CPU, so the performance is not impacted.

#### Drawbacks

DMA is the most complicated to set up and operate