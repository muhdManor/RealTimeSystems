# RealTimeSystems
MCTE 4324 (Real Time Systems)

## Week_2- LED Blinking

Using the FreeRTOS, run 2 tasks which are to toggle the built in LED with different timings, on one core in ESP32.

## Week_3 - Task Scheduling

Using the FreeRTOS, run 2 tasks in one core. One read user input to set new LED timings, another one blinks the LED according to the user input in ESP32.

## Week_4 - Memory Management

A simple serial input echo program, with optimized memory usage by using vPortFree after every serial input so that the heap memory does not build up and cause memory leak.

## Week_5

A queue in a real-time operating system (RTOS) is a kernel object that is capable of passing information between tasks without incurring overwrites from other tasks or entering into a race condition. Using Queues, Task A prints any new messages it receives from Queue 2 while reading any Serial input from the user and echo the input to the serial input. If the user enters “delay” followed by a space and a number, it should send that number to Queue 1. 

Next, Task B should read any messages from Queue 1. If it contains a number, it should update its delay rate to that number (milliseconds). It should also blink an LED at a rate specified by that delay. Additionally, every time the LED blinks 100 times, it should send the string “Blinked” to Queue 2. You can also optionally send the number of times the LED blinked (e.g. 100) as part of struct that encapsulates the string and this number.
