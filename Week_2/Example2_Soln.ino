// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

// for incoming serial data
int incomingByte = 0;   

// Pins
static const int led_pin = 22;

// Globals
static int led_delay = 1000;   // ms

//*****************************************************************************
// Tasks

// Task: Blink LED at rate set by global variable
void toggleLED(void *parameter) {
  while (1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(led_delay / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(led_delay / portTICK_PERIOD_MS);
  }
}

void readSerial(void *parameters) {

  // Read Serial Input
  while (1) {
    if (Serial.available() > 0) {
    incomingByte = Serial.parseInt(); //read next valid integer, if timeout returns 0
    if (incomingByte > 0)
      {
        led_delay = incomingByte;
        Serial.println("New LED Blinking Rate: ");
        Serial.print(led_delay);
        }
      }
    }
  }

void setup() {

  Serial.begin(115200);
     vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println("Enter a number in milliseconds to change the LED rate.");
  pinMode(led_pin, OUTPUT);

  // Start blink task
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
            toggleLED,      // Function to be called
            "Toggle LED",   // Name of task
            1024,           // Stack size (bytes in ESP32, words in FreeRTOS)
            NULL,           // Parameter to pass
            1,              // Task priority
            NULL,           // Task handle
            app_cpu);       // Run on one core for demo purposes (ESP32 only)
            
  // Start serial read task
  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
            readSerial,     // Function to be called
            "Read Serial",  // Name of task
            1024,           // Stack size (bytes in ESP32, words in FreeRTOS)
            NULL,           // Parameter to pass
            1,              // Task priority (must be same to prevent lockup)
            NULL,           // Task handle
            app_cpu);       // Run on one core for demo purposes (ESP32 only)

  // Delete "setup and loop" task
  vTaskDelete(NULL);
}

void loop() {
  // Execution should never get here
}
