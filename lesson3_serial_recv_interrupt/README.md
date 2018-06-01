# Lesson 3: Interrupt-based UART receive and including external files

[Landing Page: Intro and Required Hardwares](../README.md)

[Lesson 0: Setup and Blinking LED](../lesson0_intro_blinkLED/README.md)

[Lesson 1: UART and Hello World](../lesson1_serial_helloworld/README.md)

[Lesson 2: External Interrupts](../lesson2_external_interrupt/README.md)

Lesson 3: Interrupt-based UART Receive and External Files **`THIS LESSON`** 

## Introduction

In [Lesson 1](../lesson1_serial_helloworld/README.md) we looked at how to send data via UART. While undeniably important, a lot of applications requires reading from UART as well, which is often the tricky part.

In this lesson we'll look at utilizing internal interrupts to implement an efficient UART receive algorithm. I'm also going to introduce how to include external files to the current project to reduce clutter. This will also give you an idea on how to write your own libraries that you can reuse between different projects.

## Preparation

We'll be expanding upon [Lesson 1](../lesson1_serial_helloworld/README.md), so make a copy of the [project file](../lesson1_serial_helloworld/sample_code) and double check [the hookup](../lesson1_serial_helloworld/README.md#hookup).

Since we'll be using the RX line this time, connect an extra jumper wire from **`dev board RXD`** to **`serial adapter TXD`**.

## UART Setup

We have already done most of the setups in Lesson 1, there is just one more setting we need to change.

Open the `test.ioc` file and go to the `Configuration` page, click on the NVIC button, and enable the `USART1 global interrupt`

![Alt text](resources/cubeint.png)

This enables all USART1 interrupts, and we will use a few of them to implement our receive algorithm. Regenerate the code and launch the IDE.

## Reading from UART

### Problems with Blocking I/O

As we touched upon in the first lesson, there are [multiple I/O modes](../lesson1_serial_helloworld/hal_io_modes.md) you can use with STM32 peripherals. We used blocking mode `HAL_UART_Transmit()` in that lesson, which is simple and gets the job done.

However the problem of blocking mode becomes apparent when it comes to receiving data. Looking at the `HAL_UART_Receive()`function:

```
HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
```

In this function you must specify how many bytes you want to receive, it will then block until it has received that amount, or timeout.

The trouble is that we usually don't know how much data are coming or when. So when using blocking I/O for UART receive, the majority of CPU time is going to be wasted just waiting for data to arrive, and we can't do anything else. This is why interrupt mode makes much more sense in this case. The interrupt only fires when new data arrives, and you can carry on doing other tasks in the meantime.

### Interrupt-based UART Receive

As usual, we take a look at provided library file to see what we can use. In this case it's [stm32f0xx_hal_uart.h](sample_code/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_uart.h) and [stm32f0xx_hal_uart.c](sample_code/Drivers/STM32F0xx_HAL_Driver/Src/stm32f0xx_hal_uart.c).

Just like [last time](../lesson1_serial_helloworld/README.md), we'll find a number of I/O functions for UART:

![Alt text](resources/ioop.png)

Only this time we're going to use interrupt-based IOs that ends in `_IT()`. Specifically, `HAL_UART_Receive_IT()`:

```
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
```
`huart` is the device handle that was generated automatically in `main.c`, `pData` is an array of `unsigned char` where received data is stored, and `Size` is the number of bytes you want to receive. Obviously, the size of `pData` array should be bigger than `Size`, otherwise buffer overflow may occur.

Once this function is called, the corresponding callback/ISR will fire when `Size` number of bytes have been received, and they'll be stored in the `pData` buffer.

There are a number of ways of setting this up, and you're free to experiment. But since most of the time we don't know exactly how much data is coming, I usually set the `Size` to 1. This way an interrupt fires every time a byte is received, and then we can store that byte into a separate buffer and decide follow-up actions.

### ISR/Callbacks

As we touched upon in [the last lesson](../lesson2_external_interrupt/README.md), interrupt callback functions all have `__weak` attribute, and alway ends with `Callback`. So if you define another function with the **same name and arguments** somewhere else, the compiler will use the new one instead. This is how you should write your own ISR functions.

We can see a bunch of those weak callback functions in the [stm32f0xx_hal_uart.h](sample_code/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_uart.h):

![Alt text](resources/uartcallbacks.png)

The names are more or less self-explanatory, and it's easy to see that `HAL_UART_RxCpltCallback()` is the one we're looking for.

### Putting it together

First we declare our buffer. Since it holds only one byte, I'm going to call it `uart_byte_buf`:

![Alt text](resources/globalv.png)

Then we need to start the interrupted-based UART receive. Call the function before the main loop:

![Alt text](resources/beforeloop.png)

Finally we need to write our own callback function. Remember that the name and arguments has to be exactly the same as the provided `__weak` functions in the library `.c` file. You can put it anywhere, in this case I put it between the `USER CODE 0` block:

![Alt text](resources/callback.png)

It simply prints out whatever is received, then start a new interrupted-based UART receive.

That's it! Compile and upload. You can find the finished code [here](sample_code/Src/main.c).

Try out this simple example by sending some characters through the serial monitor, and it will print back what was received. This process is entirely interrupt-based, so no time is wasted when no data is coming.

![Alt text](resources/hello.png)

However, you'll quickly notice that only the first few letters will be printed back. This is because in this ISR we're printing out 14 bytes for each new byte coming in. This takes a huge amount of time, and as a result the new incoming data was dropped.

So again, don't forget to **`Keep your ISR as short as possible`**. Take a look at [good ISR practices](https://betterembsw.blogspot.co.uk/2013/03/rules-for-using-interrupts.html) for a refresher.

What should we do in this case then? One good approach is to simply store the incoming byte in another buffer, then check it periodically in the main loop. This way the ISR is kept quick and short, reducing the possibility of data loss.

We'll implement this approach in the next section.

## Including External Files

So far we have put all our code in `main.c`. This is fine for simple examples, but in real life projects the complexity will quickly go out of control and create a huge mess. A better solution is to write your code in separate files and include them in `main.c`, just like those [driver files](sample_code/Drivers/STM32F0xx_HAL_Driver/Inc) that we've been looking at.

In this section we'll implement a linear buffer for UART receive as a pair of `.h` and `.c` files, then include and use them in `main.c`.

### Recommended Readings

If you need a refresher on including files in C, [here is a simple example](https://stackoverflow.com/questions/7109964/creating-your-own-header-file-in-c).

There is also [a comprehensive guide](resources/CHeaderFileGuidelines.pdf) made by University of Michigan which is much more detailed and technical.

### Preparations

Create an empty `linear_buf.h` file in the `Inc` folder, and `linear_buf.c` in the `Src` folder.

![Alt text](resources/names.png)

As with best practice, we put an include guard in`linear_buf.h`:

```
#ifndef LINEAR_BUF_H
#define LINEAR_BUF_H

// code goes here

#endif
```

Now go back to Keil IDE, right click `Application/User` folder, and select `Add Existing Files to...`

![Alt text](resources/add.png)

Since we'll be adding both `.c` and `.h` files, select `All files` in file type menu.

![Alt text](resources/allfiles.png)

Now go to the respective folders and add both `linear_buf.h` and `linear_buf.c` to our project.

![Alt text](resources/select.png)

Now the new files should appear in the project explorer on the left. And don't forget to actually `#include` the header file in `main.c` between the `USER CODE Includes` block.

![Alt text](resources/included.png)

Press `F7` to compile our project with the new files, and it should do so without error.

![Alt text](resources/compile.png)

### Building it up

So far there is nothing in our pair of `linear_buf` files, and it's up to us to implement it. We want to store the incoming byte from UART in a buffer, and have an easy way to check if some action should be taken.

Let's focus on the buffer part first, while we can simply declare an `char` array, it is cleaner and more modular to put everything into a `struct`, which is what we're doing.

In the header file `linear_buf.h`, between the include guards, we declare a `struct` called `linear_buf`:

```
#define LB_SIZE 256

typedef struct
{
	int16_t curr_index;
	char buf[LB_SIZE];
} linear_buf;
```

The `LB_SIZE` marco denotes the size of the buffer, you can change it depending on your need. Keep in mind that this space is allocated in the RAM, which is 4KB in the board we're using.

Then inside the `linear_buf` struct, we have `curr_index` pointing to the end of data currently in the buffer, as well as the `buf` itself. The operating principle therefore is very simple: 

* Initially the buffer is empty, and `curr_index` points to the first element in the `buf` array:

![Alt text](resources/111.png)

* When a new byte arrives from UART, we store it where `curr_index` is pointing, then increment `curr_index`:

![Alt text](resources/222.png)

* This goes on as more data arrives:

![Alt text](resources/333.png)

* Until all data has been received and stored in the buffer:

![Alt text](resources/444.png)

* At this point we can retrieve the data and reset the buffer, after which the process starts all over again:

![Alt text](resources/111.png)
