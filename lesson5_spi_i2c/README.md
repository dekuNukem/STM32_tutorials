# Lesson 3: SPI and I2C

[Landing Page: Intro and Required Hardwares](../README.md)

[Lesson 0: Setup and Blinking LED](../lesson0_intro_blinkLED/README.md)

[Lesson 1: UART and Hello World](../lesson1_serial_helloworld/README.md)

[Lesson 2: External GPIO Interrupts](../lesson2_external_interrupt/README.md)

[Lesson 3: UART Receive and External Files](../lesson3_serial_recv_interrupt)

[Lesson 4: Timers and PWM](../lesson4_timers_and_pwm/README.md)

**`THIS LESSON`** Lesson 5: SPI and I2C

## Introduction

SPI and I2C are two very popular communication protocols in the field of embedded systems. Countless sensors, memories, and peripheral chips use one of those to talk to the master. So it's only natural that we look at how to use them with STM32.

## Recommended Readings

If need a refresher on how the two protocol works, Sparkfun has introductory tutorials on both [SPI](https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi) and [I2C](https://learn.sparkfun.com/tutorials/i2c) protocols.

More details can be found on Wikipedia: [SPI](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus) [I2C](https://en.wikipedia.org/wiki/I%C2%B2C).

## STM32 SPI Communication

