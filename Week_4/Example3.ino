// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// Settings
static const uint8_t msg_len = 255;

// Globals
static char *msg_ptr = NULL;
static volatile uint8_t msg_flag = 0;
char msg[msg_len];
static char c;
uint8_t idx = 0;
//*****************************************************************************

// Task A: Read serial input and allocate memory

void readSerial(void *parameters) {

  // Clear whole message
  memset(msg, 0, msg_len);
  
  // Loop forever
  while (1) {
    // Read cahracters from serial. 
    // If message buffer is still in use, ignore message.
    if ((msg_flag == 0)&&(Serial.available()))
    {
      c = Serial.read();
      msg[idx] = c;
      idx++;
      
      // Create a message buffer for print task
      if (c == '\n') {
        // The last character in the string is '\n', so we need to replace
        // it with '\0' to make it null-terminated
        msg[idx - 1] = '\0';
        //Allocate memory and copy over message
        msg_ptr = (char *)pvPortMalloc(idx * sizeof(char));
        // If malloc returns 0 (out of memory), throw an error and reset
        configASSERT(msg_ptr);
        // Copy message
        memcpy(msg_ptr, msg, idx);
        // Notify other task that message is ready
        msg_flag = 1;
        //Reset receive buffer and index counter
        memset(msg, 0, msg_len);
        idx = 0;
      }
    }
  }
}

// Task B: print message whenever flag is set and free buffer
void printMessage(void *parameters) {
  while (1) {

    // Wait for flag to be set and print message
    if (msg_flag == 1) {
      Serial.println(msg_ptr);
      // Give amount of free heap memory
      Serial.print("Free heap (bytes): ");
      Serial.println(xPortGetFreeHeapSize());

      // Free buffer, set pointer to null, and clear flag
      vPortFree(msg_ptr); // Without this, the heap memory will build up with each serial input.
      msg_ptr = NULL;
      msg_flag = 0;
    }
  }
}

//*****************************************************************************
// Main (runs as its own task with priority 1 on core 1)

void setup() {

  // Configure Serial
  Serial.begin(115200);

  // Wait a moment to start
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("Enter a string");

  // Start Serial receive task
  xTaskCreatePinnedToCore(readSerial,
                          "Read Serial",
                          1024,
                          NULL,
                          1,
                          NULL,
                          app_cpu);

  // Start Serial print task
  xTaskCreatePinnedToCore(printMessage,
                          "Print Message",
                          1024,
                          NULL,
                          1,
                          NULL,
                          app_cpu);
  
  // Delete "setup and loop" task
  vTaskDelete(NULL);
}

void loop() {
  // Execution should never get here
}
