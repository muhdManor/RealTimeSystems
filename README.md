# RealTimeSystems
MCTE 4324 (Real Time Systems)

## Week_2- LED Blinking

Using the FreeRTOS, run 2 tasks which are to toggle the built in LED with different timings, on one core in ESP32.

## Week_3 - Task Scheduling

Using the FreeRTOS, run 2 tasks in one core. One read user input to set new LED timings, another one blinks the LED according to the user input in ESP32.

## Week_4 - Memory Management

A simple serial input echo program, with optimized memory usage by using vPortFree after every serial input so that the heap memory does not build up and cause memory leak.

## Week_5

A queue in a real-time operating system (RTOS) is a kernel object that is capable of passing information between tasks without incurring overwrites from other tasks or entering into a race condition. Using two queues and two task, where the Serial task will read serial input and echo the contents, if the content is delay x, the value x is parsed to the delay queue. Task Blinky will receive anything from the delay queue to update the blinking LED delay and send a message to the message queue everytime the LED reaches 100 blinks. The Serial task will also read the message queue and display the message whenever the queue is filled.
