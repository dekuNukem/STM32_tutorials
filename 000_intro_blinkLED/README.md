# Lesson 000: A Complete Walkthrough of Board Detail, Softwares, and Blinking LED.

Previous lesson: [Introduction and required hardwares](../README.md)

In this lesson we're going to take a detailed look at the chip and the dev board, learn how to hook it up to the programmer, install required softwares, set up the microcontroller, and finally write our very own "Blink" program!

That's quite a bit of work, and it's going to take a while. However, this is the most important lesson of them all since it walks you through the entire process in detail. Once you persevere, you can use it on any other STM32 variant you want.

## The chip

We will be using the **STM32F030F4P6** chip throughout this tutorial series. Out of the hundreds of STM32 variants, this is actually the cheapest and most basic chip available. And here is its specs:

![Alt text](resources/spec.png)

Now it might sound counterintuitive to start from the bottom of the line, but I do have some very good reasons:

* They are cheap. A single chip is 50 cents, and a compete dev board is only $1.5.

* They are simple enough for first timers to get going quickly. 

* Despite the lowly status, they are still very capable and contain all the basic peripherals we're going to cover.

* All you learned working with this chip also applies to all other STM32 chips, so you can easily step up after you're done.


Now let's take a look at the pinout of this chip, taken from [the datasheet](../resources/datasheets/stm32f030f4p6.pdf):

![Alt text](resources/tssop20pinout.png)

Unlike Arduino where pins are referred to by simply a number(pin 1, pin 2...), GPIO pins on bare microcontrollers like STM32 usually has a *port* and *number* associated with them. A *port* is a set of pins that are organized internally and can be controlled together. In STM32, GPIO ports are named alphabetically starting from A, and each port can have up to 16 pins from 0 to 15.

As a result, GPIO pins on STM32 are named like `PXY`, which stand for 'Port X pin Y'. Due to size limits not all chips will have all the ports, and not every port will have all its 16 pins. In this case, most of the pins are from port A(PA0 to PA14). Port B only has 1 pin(PB1), and Port F has 2(PF0 and PF1).

There are also some non-GPIO pins common to all STM32 chips that are worth mentioning:

| Pin name | Function                                             |
|----------|------------------------------------------------------|
| VSS      | Ground                                               |
| VDD      | 3.3V Supply                                          |
| VDDA     | Analog supply for ADC and DAC. Usually equal to VDD. |
| VBAT     | Battery input for RTC and low-power backups	      |
| NRST     | Active low reset. Pulled up internally.              |
| Boot0    | Boot mode. Low: normal startup, High: run bootloader |

That pretty much covers all you need to know for the moment. Let's move on to the dev board.

## The dev board

By now you should have all three pieces of hardwares ready: the dev board itself, the ST-Link v2 programmer, and the USB serial adapter:

![Alt text](resources/all3.jpg)

Let's take a closer look at the dev board itself with added annotations:

![Alt text](resources/board_annotated.jpg)

All in all a clean, simple, and versatile little board. Something to note:

* All pins have been broken out on the header.

* The micro USB connector is for power only, since this chip doesn't have USB capability.

* All STM32 chips run at 3.3V, but are 5V tolerant on *digital* pins.

* Don't worry about the BOOT0 selector, leave it on the default GND side. (aka normal startup)

## Hookup

Now let's hook it up to the programmer so we can upload our programs into it. We're using ST's SWD debugging interface, which only require 2 wires plus power.

Plug the 4 wires into `SWDIO`, `GND`, `SWCLK` and `3.3V` pins on the programmer:

![Alt text](resources/stlinkheader.jpg)

And connect the other end accordingly into the programming header on the dev board.

![Alt text](resources/hookup.jpg)

That's it! Hope that wasn't too hard for you. The programmer also powers the board when it's plugged in.

## Softwares

We're doing the development under Windows, as it is the easiest way to get started. Of course you can set up your own toolchain in Linux, but that is going to be later.

There are 3 softwares that you need to install, all of which free:

### STM32 ST-LINK utility

A useful utility through which you can view/wipe the flash memory, dump/upload firmwares, adjust chip settings, etc. It also contains the driver for the ST-Link programmer that you just bought.

Go to the official site:

http://www.st.com/en/development-tools/stsw-link004.html

Click the blue "get software" button at the bottom of the page:

![Alt text](resources/getutil.png)

It will then ask for your name and email. Give it some fake name and [generate a fake email](https://www.guerrillamail.com) to get the download link.

Run the installer, it will ask you to install the driver, click install.

![Alt text](resources/utilinstall.png)

After it's done, plug in the programmer with the board into a USB port:

![Alt text](resources/plugged_in.jpg)

If your wiring is correct, the power LED should light up. The user LED might start blinking too if the seller burned a demo program into it, which is kind of a spoiler, but let's ignore that for now.

Windows should install some drivers automatically, wait for it to finish. Then open up the STM32 ST-LINK utility you just installed, click the connect button. 

![Alt text](resources/beforeconnect.png)

If the hookup is still correct, the memory content should now appear in the main window:

![Alt text](resources/connected.png)

If everything works, congrats! You can move on to the next software now. There are also some tools in the `Target` menu to play with should you feel adventurous.

### STM32CubeMX

STM32CubeMX is an interactive configuration tool and code generator. It lets you set up the microcontroller in a straightforward graphical interface, then generates the initialization code so you don't have to write any. Pretty neat!

Just like the first one, go to the official link below, click the blue "Get Software" button near the bottom, and download it:

http://www.st.com/en/development-tools/stm32cubemx.html

Inside the zip there are 3 copies for different platforms. You'll want to run the windows one:

![Alt text](resources/threeopt.png)

Click through with defaults. If you don't have Java it will ask you to install it. After it's all said and done, we can move on to the third and final software.

### Keil MDK-ARM

Keil is considered one of the "standard" IDEs in embedded development, it has a large community, and offers excellent compiler and debugging tools. And as you would expect, it is non-free. A license costs thousands of dollars, and a 32KB code size limit is enforced otherwise.

There is a silver lining however, as ST provides a **free license for all STM32F0 parts** with no code size limit at all. The aim is to get more people into STM32, and I guess it's working.

Anyway, F0 is more than capable for the majority if projects, you can it have up to 100 pins, 256KB flash, and 32KB of RAM. And when you do grow out of the F0 series, you can set up the open source arm-gcc compiler and get rid of the license issue all together.

Go to the offcial link below, fill in the form and download the installer. Again, use a [fake identity](http://www.fakenamegenerator.com/) to protect your privacy:

https://www.keil.com/demo/eval/arm.htm

Click through the installer with default settings. It will take a bit and install some drivers. After the installation is finished it will automatically open the "Pack Installer" and start to download some software packages. Just wait for it to finish, you can see the progress on the bottom right corner.

![Alt text](resources/packdl.png)

The lists will fill up after it's done. We can quit the program for now.

![Alt text](resources/packdone.png)

That's it! All three program installed. We're ready to actually start writing our first STM32 program now!

## The Blinky LED

The simple blinking LED is the "hello world" of embedded systems. It's probably your first Arduino program, and we're going to do it all over again with STM32. The process involves configuring the chip in STM32CubeMX, generating the initialization code, writing your own code, and compile then upload. This process is the same with any STM32 chips.

### Chip configuration in STM32CubeMX

#### Selecting the target chip

Open up STM32CubeMX and click `New Project`:

![Alt text](resources/cubehome.png)

It might start to check for updates, eventually you'll end up here:

![Alt text](resources/cubenew.png)

As you can see it's quite a comprehensive list, and you can browse by series, package, features, cost, etc.

We need to find which chip we're using, and since we already know the part number `STM32f030F4`, we just need to type it in the search box:

![Alt text](resources/cubefound.png)

Double click the listing to select this chip:

![Alt text](resources/cubeblank.png)

Now we're in a nice chip configuration view! On the left side is a list of available peripherals, and on the right side is a illustration of the chip itself. You can zoom in/out using mouse wheel, move it around with left click, and rotate it with the buttons on the toolbar above to suit your needs.

We do need to configure a few peripherals, so let's begin.

#### Enable SWD

First up we need to enable SWD in order to upload the firmware into the chip. Expand `SYS` node and check the `Debug Serial Wire ` box:

![Alt text](resources/cubeswd.png)

You can see the PA14 and PA13 pins are automatically highlighted on the right side, indicating they are being used.

#### Enable External Clock Source

There is an external crystal oscillator on the dev board, and we're going to use that to run the chip. 

Expand RCC (Reset and Clock Control) node, select `Crystal/Ceramic Resonator` for HSE.

![Alt text](resources/cubeext.png)

#### Enable GPIO Output

Finally we need to set a GPIO pin to output. We're going to use the LED that's connected to PA4 on our dev board.

*Left* click on PA4 then select `GPIO_Output`:

![Alt text](resources/cubepa4.png)

This sets the function of PA4 to GPIO Output, after that *right* click on PA4 again and select `Enter User Label` to give it a fancy name, I'm calling it `USER_LED`.

![Alt text](resources/cubename.png)

That's all for peripherals! We now have some heady stuff coming up.

#### A Brief Intro on STM32 Clock Signals

Before the next step, I think it would be a good idea to first get you familiar with various clock signals that STM32 utilizes, so here it goes:

##### Internal Clocks

Those clock sources are inside the chips themselves, they are always available, but generally less accurate. Members are:

| Clock | Frequency | Description                                                                                                 |
|-------|-----------|-------------------------------------------------------------------------------------------------------------|
| LSI   | ~40KHz    | Low Speed Internal. Highly unstable, avoid.|
| HSI   | 8MHz      | High Speed Internal. Can be used for system clock.                                                           |
| HSI14 | 14MHz     | Used for ADC.                                                                                                |
| HSI48 | 48MHz     | Only on USB capable chips. Can be used for system clock.                                                                               |

LSI is uncalibrated and inaccurate, avoid at all cost.

HSI and HSI48 work fine if no precise timekeeping is required, otherwise an external crystal is recommended.

##### External Clocks

You can also supply 2 clock signals externally for more accuracy:

| Clock | Frequency         | Description                                |
|-------|-------------------|--------------------------------------------|
| LSE   | Usually 32.768KHz | Low Speed External. Used for RTC timekeeping.   |
| HSE   | 4 - 32MHz         | High Speed External. Used for system clock |

A crystal oscillator is usually utilized for external clocks, as is the case with the dev board we're using.

#### Configuring the Clock Tree

We're ready for the clock tree! Click `Clock Configuration` tab:

![Alt text](resources/cubeclktree.png)

Now this is some proper heady stuff. Don't worry though, I provided a completed set-up below. Follow the yellow path and I'll explain along the way:

![Alt text](resources/cubeclk_anno.png)

We start from the very beginning of the yellow path.

![Alt text](resources/cubehse1.png)

We can see HSE is available since we're using an external crystal. The `input frequency` is set to 8MHz, you can change it if you're using a different crystal.

![Alt text](resources/cubehse2.png)

Next we encounter a clock divider. 8MHz is already pretty slow so we leave it at 1.

![Alt text](resources/cubehse3.png)

Next we run into the `PLL source Mux`. We use PLL(Phase Locked Loop) to multiply the input to 48MHz so the chip can run at full speed. Here we choose which clock goes into the PLL, in this case the HSE.

![Alt text](resources/cubehse4.png)

Here at PLL we choose how many times to multiply the input clock. We have 8MHz and want 48MHz, so 6 it is.

![Alt text](resources/cubehse5.png)

Now we arrive at `System Clock Mux`, which determines what to use to clock the entire system. PLL output in this case.

![Alt text](resources/cubehse6.png)

Now the 48MHz system clock is being distributed to a number of system buses and peripherals. There's no need to worry about the details here, just keep everything under the max frequency and it'll be fine.

That's pretty much it! I hope it made sense. The clock tree might be more complicated on higher end STM32 chips, but the basic principle still stands.

As an exercise, try figure out how to use the HSI through PLL as the system clock. Click here to see the answer.

#### Peripheral Configurations

We're almost there! Click the "Configuration" tab for the, well, configuration view. Here you can adjust the settings of all peripherals that you enabled on the first page. Since we only enabled a GPIO, click the `GPIO` button.

![Alt text](resources/cubeconfig.png)

One the new window, select a pin to change its setting.

There actually isn't much to change in this case, but it would help to get familiar with the options:

![Alt text](resources/cubegpioconfig.png)

GPIO Output level: High or Low. The initial output level of the pin.

GPIO Mode: Push-Pull or Open-Drain. In short PP can drive a signal both high and low, while OD can only pull the signal low. Read more [here](https://learn.adafruit.com/adafruit-1-wire-gpio-breakout-ds2413/open-drain-gpio) and [here](https://en.wikipedia.org/wiki/Open_collector).

Pull-up/Pull-down: [Read more about it here](https://learn.sparkfun.com/tutorials/pull-up-resistors), for output we use neither.

Maximum output speed: Sets the slew rate of output signal. Leave it to default setting.

Click OK to go back, that was all the configuration done, we can finally generate our code now!

#### Generating the code

Now we'll have the STM32CubeMX generate all the initialization code so we don't have to write any.

To begin click `Project` menu then `Settings`:

![Alt text](resources/cubesetting.png)

Enter a project name and select its location, select `MDK-ARM V5` as our IDE, don't touch anything else:

![Alt text](resources/cubesat1.png)

Go to `Code Generator` page, and select `copy only the necessary library files`. It's not strictly necessary but I like to keep it clean.

![Alt text](resources/cubesat2.png)

Click OK. If it's the first time running, it will ask you to download a firmware package, confirm and wait for it to finish.

After all that we finally get to generate the code! Click `Generate Code` under `Project` menu:

![Alt text](resources/cubecode.png)

Hooray!

![Alt text](resources/cubecode1.png)

You can find the generated code in the folder you selected. The `.ioc` file is the STM32CubeMX project you've been working on, and the MDK project is inside `MDK-ARM` folder.

![Alt text](resources/cubefile.png)

Anyway, click `Open Project` to launch the Keil IDE.

![Alt text](resources/cubecode2.png)

### (Finally) My First STM32 Program

#### First time setup:

If it's the first time MDK is running, the "Pack Installer" will pop up again and ask you to install another package:

![Alt text](resources/mdkpac.png)

Confirm and wait for it to finish.

If you see this afterwards, click `Yes`:

![Alt text](resources/mdkerr.png)

Then select our chip from the list:

![Alt text](resources/mdksel.png)

After all that, you're be greeted with this:

![Alt text](resources/mdkhome.png)

There are a few things we need to change. Click `Flash` menu then `Configure Flash Tools`

![Alt text](resources/mdkmenu.png)

Then the `Settings` button:

![Alt text](resources/mdksat.png)

First uncheck `Verify` then check `Reset and Run`. This allows your program to start running right away after uploading instead of having to press the reset button every time.

If the `Programming Algorithm` box is empty, press the `Add` button and select the `STM32F0xx 16kB Flash` entry and press `Add`.

![Alt text](resources/mdkcheck.png)

Press `OK` a few times to go back to the main screen.

#### Coding Blink

Find and open `main.c` by expanding the folders and double clicking on the file:

![Alt text](resources/mdkmain.png)

Skim through the code, you'll find the code generator left comments that you put your own code inbetween. As a rule:

### ALWAYS PUT YOUR CODE BETWEEN `/* USER CODE BEGIN */` AND `/* USER CODE END */` 

This way, your code will be persevered during subsequent STM32Cube code regenerations. You can use the built-in editor, however if you prefer using an external editor you might want to [turn on the file auto-reload](mdk_auto_reload.md).

Let's take a look at the `main()` function.

```
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */
  /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

```

It's apparent that the generated code first initializes all peripherals, then go into a loop doing nothing. It also left plenty of user code spaces, so let's fill them in with our first "blink" program.

Right away we have a problem: Arduino has `digitalWrite()`, what do we use here? The answer to this, and in fact every other peripheral is to **look at the available functions in the corresponding HAL driver header file**. They are located in `project_folder/Drivers/STM32F0xx_HAL_Driver/Inc`

HAL stands for Hardware Abstraction Layer. STM32 HAL library is a open source library written by ST and recommended for all new projects. The function call stays the same across different families and parts, and you don't have to worry about manipulating registers. This means the code is easy to understand and easy to port as well.

Since this is GPIO, let's take a look what functions are available in `stm32f0xx_hal_gpio.h`, after scrolling down a bit we see:

![Alt text](resources/mdkgpio.png)

The first 3 looks promising, and particularly the `HAL_GPIO_WritePin`



We also need a delay function like Arduino's `delay()`, here it is called `HAL_Delay()`. It runs off the sysTick timer and is in milliseconds.

Let's take a look at the completed blink code snippet:

```
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
HAL_Delay(200);
HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
HAL_Delay(200);
```

Pretty straightforward. The first argument of `HAL_GPIO_WritePin` is the GPIO port, which is a marco called `GPIOA`, it can also be `GPIOB`, `GPIOC`, etc. The second argument is the pin number, since it's PA4 



