# RealTimeSystems
MCTE 4324 (Real Time Systems)

## Week_2- LED Blinking

Using the FreeRTOS, run 2 tasks which are to toggle the built in LED with different timings, on one core in ESP32.

## Week_3 - Task Scheduling

Using the FreeRTOS, run 2 tasks in one core. One read user input to set new LED timings, another one blinks the LED according to the user input in ESP32.

## Week_4 - Memory Management

A simple serial input echo program, with optimized memory usage by using vPortFree after every serial input so that the heap memory does not build up and cause memory leak.

## Week_5- Queue

Using Queues, One task performs basic echo on Serial and sends number (in a queue) to the second task. If it receives a message in a second queue, it prints it to the console. The second task blinks an LED. When it gets a message from the first queue (number), it updates the blink delay to that number. Whenever the LED blinks 100 times, the second task sends a message to the first task to be printed.

## Week_6- Mutex

Using Mutex, the task parameter (delay_arg) is not disrupted by any other functions. With the mutex in place, the task should be able to read the parameter (parameters) into the local variable (num) before the calling function’s stack memory goes out of scope (the value given by delay_arg). In this case, the setup function finished first and dereferences the variable needed for the task before the task has finished compiling
