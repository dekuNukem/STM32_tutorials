# Lesson 3: SPI and I2C

[Landing Page: Intro and Required Hardwares](../README.md)

[Lesson 0: Setup and Blinking LED](../lesson0_intro_blinkLED/README.md)

[Lesson 1: UART and Hello World](../lesson1_serial_helloworld/README.md)

[Lesson 2: External GPIO Interrupts](../lesson2_external_interrupt/README.md)

[Lesson 3: UART Receive and External Files](../lesson3_serial_recv_interrupt)

[Lesson 4: Timers and PWM](../lesson4_timers_and_pwm/README.md)

**`THIS LESSON`** Lesson 5: SPI and I2C

## Introduction

SPI and I2C are two very popular communication protocols in embedded systems. Countless sensors, memories, and peripheral chips use one of those to talk to the master. So it's only natural that we look at how to use them with STM32.

## Recommended Readings

If you need a refresher on how those two protocol works, Elliot Williams from Hackaday has written excellent articles explaining both [SPI](https://hackaday.com/2016/07/01/what-could-go-wrong-spi/) and [I2C](https://hackaday.com/2016/07/19/what-could-go-wrong-i2c-edition/) in detail.

Sparkfun also has introductory tutorials on both [SPI](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi) and [I2C](https://learn.sparkfun.com/tutorials/i2c).

And as always you can go to Wikipedia: [SPI](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus) [I2C](https://en.wikipedia.org/wiki/I%C2%B2C).

## STM32 SPI Communication

Once again, we'll be expanding upon [Lesson 1](../lesson1_serial_helloworld/README.md), so make a copy of the [project file](../lesson1_serial_helloworld/sample_code) and double check [the hookup](../lesson1_serial_helloworld/README.md#hookup).

### SPI Setup

To use SPI, enable `SPI1` in STM32CubeMX. STM32 supports a number of different SPI modes, but `Full-Duplex Master` is the most common mode for communicating with peripheral chips, so let's select that.

STM32 also supports `Hardware NSS Signal`, where the SPI CS pin is controlled by hardware. I suggest **NOT** using it, since its behavior is often not what you want. For example when sending multiple-byte commands the hardware CS goes down then up for every byte it sends, while you most likely want it to stay down for the entire sequence. All in all it's not worth the trouble, just set a GPIO as CS and be done with it.

![Alt text](resources/cubespi.png)

I set PA3 as the CS pin, you can use whatever free GPIO pin you want.

![Alt text](resources/cubecs.png)

Go to `Configuration` tab and click the `SPI1` button to bring up its configuration window:

![Alt text](resources/cubeinit.png)

There are a number of settings that needs adjusting:

* Leave `Frame Format` at Motorola.

* `Data Size` is usually one byte, so change it to 8 bits.

* `Prescaler` changes the SPI clock speed.

* `CPCL` and `CPHA` depend on the SPI device.

* No need to touch anything in `Advance Parameters`

Of course most of those settings depends on what SPI peripheral you're using, so consult the datasheet to see what it needs.

For this simple demo I used this configuration:

![Alt text](resources/cubedone.png)

Press `OK` to save the setting. Then press the `GPIO` button to set up the new CS pin we just selected.

We just need to change the initial output level to `High` so it doesn't assert the SPI device right away.

![Alt text](resources/cubecspin.png)

That's it! Regenerate the code and launch Keil MDK.

### Using SPI

As usual, we take a look at provided library file to see what we can use. Near the end of [stm32f0xx_hal_spi.h](sample_code_spi/Drivers/STM32F0xx_HAL_Driver/Inc/stm32f0xx_hal_spi.h), we see a number of provided functions:

![Alt text](resources/spi_func.png)

Since SPI operates like two shift registers connected in a ring, you will always receive the same amount of data that you send. Therefore your best bet is to use `HAL_SPI_TransmitReceive()`. 

Generally you need to declare two buffers with the same size, one for sending and one for receiving:

![Alt text](resources/pv.png)

And when it's time, pull the CS line down, call `HAL_SPI_TransmitReceive()` with device handle, two buffers, amount of bytes to send, and a timeout.

The data from `txbuf` will be sent out, and at the same time the received data will be stored in `rxbuf`.

Don't forget to set CS pin to high afterwards:

![Alt text](resources/while.png)

You can examine the waveform using a logic analyzer:

![Alt text](resources/logic.png)

That's pretty much it for the SPI! With this knowledge you can write your own library or easily port Arduino libraries to STM32 now.

## STM32 I2C Communication

Compared to SPI