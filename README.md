# RealTimeSystems
MCTE 4324 (Real Time Systems)

## Week_2 - LED Blinking

Using the FreeRTOS, run 2 tasks which are to toggle the built in LED with different timings, on one core in ESP32.

## Week_3 - Task Scheduling

Using the FreeRTOS, run 2 tasks in one core. One read user input to set new LED timings, another one blinks the LED according to the user input in ESP32.

## Week_4 - Memory Management

A simple serial input echo program, with optimized memory usage by using vPortFree after every serial input so that the heap memory does not build up and cause memory leak.

## Week_5 - Queue

Using Queues, One task performs basic echo on Serial and sends number (in a queue) to the second task. 
- If it receives a message in a second queue, it prints it to the console. 
- The second task blinks an LED when it gets a message from the first queue (number) and updates the blink delay to that number. Whenever the LED blinks 100 times, the second task sends a message to the first task to be printed.

## Week_6- Mutex

Using Mutex, the task parameter (delay_arg) is not disrupted by any other functions. 
- With mutex, the task should be able to read the parameter (parameters) into the local variable (num) before the calling function’s stack memory goes out of scope (the value given by delay_arg). 
- The setup function finished first and dereferences the variable needed for the task before the task has finished compiling

# Week7 - Semaphore

Using Semaphores and mutexes, the writing and reading data in a buffer is not disrupted and not repeated. 
- The critical sections of the code (Serial, read & writing on buffer) such are protected by mutexes. 
- The Semaphores ensure the consumer tasks do not read the same data more than once, it only execute if the semaphores are released by the producer tasks.

## Week8 - Software Timer

Software timers are used to delay the execution of functions or carry out periodic operations. Using software timer, disable the backlight of an LCD (represented by the built in LED on the ESP32) after 5 seconds of inactivity (no input by user).

## Week9 - Hardware Interrupts
Sampling, processing, and interface system using hardware interrupts and kernel objects.

- Implement a hardware timer in the ESP32 that samples from an ADC pin once every 100 ms. This sampled data should be copied to a double buffer. When one of the buffers is full, the ISR notify Task A.

- When Task A receives notification from the ISR,wake up and compute the average of the previously collected 10 samples and when finished,update a global floating point variable that contains the newly computed average. 

- Task B should echo any characters received over the serial port back to the same serial port. If the command “avg” is entered, it should display whatever is in the global average variable.

## Week10 - Deadlock & Starvation
Solve the dining philosophers problem using the demo code 

## Week11 - Priority Inversion
Original code:  Task H is blocked for around 5 seconds waiting for a mutex to be released from Task L. Task M interrupts task L for those 5 seconds, causing unbounded priority inversion.

- Use the critical section guards to prevent the scheduler from interrupting during the critical section in Task H and Task L.
