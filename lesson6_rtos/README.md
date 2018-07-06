# Lesson 6: UART and Hello World

[Landing Page: Intro and Required Hardwares](../README.md)

[Lesson 0: Setup and Blinking LED](../lesson0_intro_blinkLED/README.md)

[Lesson 1: UART and Hello World](../lesson1_serial_helloworld/README.md)

[Lesson 2: External GPIO Interrupts](../lesson2_external_interrupt/README.md)

[Lesson 3: UART Receive and External Files](../lesson3_serial_recv_interrupt)

[Lesson 4: Timers and PWM](../lesson4_timers_and_pwm/README.md)

[Lesson 5: SPI and I2C Communication](../lesson5_spi_i2c/README.md)

**`THIS LESSON`** Lesson 6: Real-time Operating Systems (RTOS)

## Introduction

So far, we have been writing programs and executing them inside a big `while` loop in `main.c`. This single-threaded approach is simple, straightforward, and more than adequate for a large portion of embedded applications.

However, this becomes inadequate or overly complicated in some situations.  Imagine you're designing a control panel that needs to carry out a number of tasks such as reading key inputs, updating a display, reading sensors, parse incoming data, setting outputs, etc.

Those tasks take different amount of time to complete, and need to be executed at different intervals with different priorities. I guess you can imagine it would be a nightmare to set up in a single-threaded environment, and if one task bogs down or hangs, the entire system crashes.

This is where **Real-time Operating System** comes in. Just like the desktop OS you're using, RTOS allows you to define tasks that **run in parallel**. Thus freeing you from having to manage the timing yourself.

RTOS achieves the illusion of concurrent execution by running each task for a short time then switch to another. By doing this hundreds of times a second, it feels like all the tasks are executing at the same time. The job of determining which task to run (and for how long) and which task to put to sleep is called **task scheduling**.

To witness RTOS in action, we're going to set up the open-source FreeRTOS on our STM32 board and create two tasks in this lesson.

## Recommended Readings

Predictively, the description of RTOS above is extremely simplified and generalized. You can find some introductory guides with slightly more details below:

* [What is RTOS?](https://www.freertos.org/about-RTOS.html)

* (Another one) [What is RTOS?](https://www.highintegritysystems.com/rtos/what-is-an-rtos/)

* [FreeRTOS Tutorial](https://www.freertos.org/tutorial/)

And of course, there's always Wikipedia:

* [Real-time operating system](https://en.wikipedia.org/wiki/Real-time_operating_system)

* [Task (computing)](https://en.wikipedia.org/wiki/Task_(computing))

* [Real-time computing](https://en.wikipedia.org/wiki/Real-time_computing)

## Hookup

Once again, we'll be expanding upon [Lesson 1](../lesson1_serial_helloworld/README.md), so make a copy of the [project file](../lesson1_serial_helloworld/sample_code) and double check [the hookup](../lesson1_serial_helloworld/README.md#hookup).

## FreeRTOS setup in STM32CubeMX

In the `Pinout` page, simply check the `Enabled` box under `FREERTOS`.

![Alt text](resources/enabled.png)

For some reason, FreeRTOS doesn't like to use the default `SysTick` timer for internal timekeeping, so we have to select another timer as the time base. If you don't do this, STM32Cube will warn you at code generation, so we might as well do it now.

Expand `SYS`, and change the `Timebase Source` to one of the lesser-used timers:

![Alt text](resources/tim.png)

Click the newly appeared `FREERTOS` button in `Configuration` page:

![Alt text](resources/button.png)

A huge configuration window appears. Fortunately most of the defaults are already good, although you might want to adjust the `Memory Management settings` to suit your need.

The `TOTAL_HEAP_SIZE` is the total amount of memory that can be used by your tasks. Remember on this chip we only have 4KB RAM, so 2KB for the RTOS is a good choice.

`Memory management scheme` determines how memory can be allocated and freed with `malloc()` and `free()`. [Do read this page for details](https://www.freertos.org/a00111.html), but most of the time `heap_1.c` is enough.

![Alt text](resources/mem.png)

With the RTOS setting finished, we can define some tasks now. Click on the `Tasks and Queues` tab:

![Alt text](resources/tq.png)

We can see there is already a task called `defaultTask`. Let's make another one. Click on the `Add` button:

![Alt text](resources/t2.png)

You can change the `Task Name` to anything you like.

High `Priority` tasks will have shorter response time, and able to interrupt lower priority tasks, so set it based on your needs.

`Stack Size` determines the available stack for this task. Too little your task will crash, too much you're wasting memory. I suggest start from the default and turn it up if your task starts to behave erroneously.

`Entry Function` is the name of the actual function that you're going to write your code in, so name it accordingly.

By default STM32Cube put task functions in `main.c`. However generally the code for each task is quite long, so you don't want it to clutter up `main.c`. Therefore I suggest changing `Code Generation Option` to `Weak` so you can put the code in external files.

## Next Steps

A WORD ON WHEN TO USE RTOS

not always necessary, a lot of the simple projects dont use it

takes very little space, can even run on this

if you do end up in the while loop something is wrong, check stack and heap size.