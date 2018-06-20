# Lesson 4 Homework Hints and Answers

The goal of this homework is to **implement an accurate microsecond timebase with STM32 timers**.

You should have a **`uint32_t micros()`** function which returns the number of microseconds since start-up, and a **`delay_us(uint32_t us)`** function which delays the number of microseconds in the argument.

### Further Hints

One way to tackle this problem is to set a timer to count up at 1MHz. This way the counter goes up by 1 every microsecond, and you simply grab the counter value to get the elasped microseconds.

However, since the timer counter is only 16-bit, it will overflow at 65535, which is every 65.535ms. As a result, depending on the counter value itself for timekeeping is unreliable.

We can overcome this by setting an overflow interrupt, on which we increment a 16-bit timestamp variable in our program. This way, we effectively end up with a 32-bit microsecond counter: The upper half is stored in the timestamp variable, and the lower half is the timer counter itself.

So to recap:

* Set up a timer to count up at 1MHz

* Enable timer overflow interrupt with a period of 65535

* Increment a timestamp variable when interrupt fires

* Combine the variable and counter value to get microsecond count

### Homework Answer

You can find the [finished homework here](homework_answer).

In STM32Cube I enabled timer 14 and set its `prescaler` to 47, `counter period` to 65535, and enabled interrupt. As a result this timer counts up at 1MHz, and fires a overflow interrupt every 65535us.

I then created a pair of c files called [delay_us.h](homework_answer/Inc/delay_us.h) and [delay_us.c](homework_answer/Src/delay_us.c).

In [delay_us.c](homework_answer/Src/delay_us.c) I declared a variable `upper16`, which is incremented in the ISR. It is then combined with the counter value to generate a 32-bit microsecond timestamp.

[Consult last lesson](../lesson3_serial_recv_interrupt) is you're unfamiliar with writing and including external files.

### A Much Simpler Way

Just so you know, 32-bit timers are available on some higher-end STM32F0 chips. They overflow every 35 minutes, so if you're using them for microsecond timebase you don't have to use interrupt at all. Simply grab the counter value and be done.