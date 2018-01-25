# STM32, The Easy Way

Do you already have some experience with Arduino, and want to step up the game into proper ARM embedded system developments? If so, you're in the right place!

We're going to take a look how to get started with STM32 microcontrollers. And to lower the entry barrier, we'll be using softwares that are free, and only $4 worth of hardwares.

This tutorial is designed to be detailed and easy to follow. However, it is **NOT** meant to be a comprehensive guide. Instead it aims to get your started quickly and ease the transition from Arduino to a lower level environment.

## Why STM32?

Now there are many good reasons to stay inside the Arduino ecosystem. After all, it kickstarted the "maker" revolution in the first place. The consistent hardware, simple IDE, and the excellent community support meant it's easier than ever for people to start creating what they want, and the abstraction layer shielded them from the low-level nitty-gritties like peripheral configuration and fuse settings.

It's all well and good, and most people are perfectly content with that. However, when you look at the actual chip on most Arduinos, you'll find an aging ATmega328P, a decade old 8-bit chip with a tiny amount of RAM, limited peripherals, and a leisurely clock speed. As a result, in commercial situations 8-bitters like those have been mostly relegated to cost-sensitive applications like cheap toys. And the world has largely moved on to 32-bit microcontrollers.

Now I'm not saying 8-bit Arduinos have gone completely pointless, in fact they are excellent learning tools and more than adequate for most hobby projects. It's just **if you want to go further down the path of embedded development, plain old Arduino just simply isn't going to cut it.**

Most of the 32-bit microcontrollers today uses ARM Cortex-M architecture, examples include STMicroelectronics' STM32 line, NXP's LPC line, Atmel's own SAM line, and just about every single IoT chips out there today. Those 32-bit chips tends to run faster, have great deal of more memory and peripherals, and even cheaper than the comparable 8-bit chips.

To demonstrate, here is a comparison between Arduino and my go-to STM32 chip, STM32F072C8T6:

![Alt text](resources/images/intro_comp.png)

As you can see, the STM32 blows the ol' Arduino out of the water in just about every single aspect. And here's a brief summary:

### Advantages:

#### High performance 

see the difference above

#### Versatile, Reusable and Future-proof:

There are **hundreds** of STM32 variants to choose from. You can go from 50 cents STM32F0 up to 400MHz monsters STM32H7. All of them uses the same tool and code structure so it's trivially easy to port between them. They also mostly have the same pinout for a given package type, so you can simply drop in a more powerful chip without changing the circuit design should the needs arises.

#### Integrated Bootloaders

All STM32 have built-in bootloaders for uploading firmwares without using a programmer. This can be done through Serial, USB or even I2C, SPI and CAN bus, all without taking up user flash memory like Arduino does.

#### 5V tolerant

All digital pins on STM32 are 5V tolerant, so you can safely hook them up to legacy systems.



conclusion:
With larger flash and RAM you'll be able to develop more sophisticated programs, and with versatile peripherals there are more options of connectivity 

