# STM32 HAL I/O modes

In STM32 HAL, most of the I/O functions are available in 3 modes. We'll be using UART as example:

## Blocking Mode

In this mode you ask the peripheral to do something, and then just wait for it to finish.

Their HAL functions don't usually have suffixes, in this case it's simply called `HAL_UART_Transmit()`.

### Advantages

It's the simplest and most straightforward to use. 

### Drawbacks

Valuable CPU time is wasted while waiting, so performance takes a hit. Waiting time can be significant if peripheral is slow or a lot of transfer is involved.

## Interrupt Mode

You ask the peripheral to perform a task, then carry on doing something else. An interrupt will be raised when the task is finished.

Their HAL functions usually ends in `_IT`, in this case it's called `HAL_UART_Transmit_IT()`.

### Advantages

There is no need for waiting, the function returns immediately and you can do something else while the peripheral is working on your task. This improves the respond time and general performance.

### Drawbacks

It's slightly more complicated to set up, and can become rather chaotic as the complexity of your program picks up. There are also potential synchronization issues if you're not careful about how the data is accessed.

## DMA Mode

DMA stands for Direct Memory Access, in this mode data is transfered between memory and peripheral directly without going through CPU at all. 

### Advantages

This has the best performance and is suitable for bulky and high speed data transfers.

### Drawbacks

It is the most complicated to set up and operate, and its performance edge might not be apparent unless you're doing tons of data transfers.