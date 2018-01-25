# STM32, The Easy Way

Do you already have some experience with Arduino, and want to step up the game into proper ARM embedded system developments? If so, you're in the right place!

We're going to take a look how to get started with STM32 microcontrollers. And to lower the entry barrier, we'll be using softwares that are free, and only $4 worth of hardwares.

This tutorial is designed to be detailed and easy to follow. However, it is **NOT** meant to be a comprehensive guide. Instead it aims to get your started quickly and ease the transition from Arduino to a lower level environment.

## Why STM32?

Now there are many good reasons to stay inside the Arduino ecosystem. After all, it kickstarted the "maker" revolution in the first place. Its consistent hardware, simple IDE, and the extensive community support meant it's easier than ever for people to start creating what they want, and the abstraction layer shielded them from the low-level nitty-gritties like peripheral configuration and fuse settings.

It's all well and good, and most people are perfectly content with that. However, for some there are still reasons to dive deeper into the world of embedded systems. It could be career opportunities, performance issues, or just pure interest about how it all works below the surface. 

Whatever it is, if you look at the actual chip on most Arduinos, you'll find an ATmega328P, an aging decade old 8-bit chip with tiny amount of system memory, limited peripherals, and a leisurely clock speed of 16MHz. As a result, in commercial situations 8-bitters like those have been mostly relegated to cost-sensitive applications like cheap toys. And the world has moved on to 32-bit microcontrollers.

Most of the 32-bit microcontrollers today uses ARM Cortex-M architecture, examples include STMicroelectronics' STM32 line, NXP's LPC line, Atmel's own SAM line, and just about every IoT chip out there today. Those 32-bit chips tends to run much faster, have great deal of more memory and peripherals, and even cheaper than comparative 8-bit chips.

To demonstrate, here is a comparison between Arduino and my go-to STM32 chip, STM32F072C8T6:


As a result, if you want to develop your own product or something else it makes more sense to use a STM32 than aging old arduino.