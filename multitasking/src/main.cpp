#include <Arduino.h>
#include <cstdint>

// create 2 tasks
// one task will increment a global counter and sleep for 1 second
// the other task will toggle the led high if the counter % 4 < 2, else toggle the led low, and sleep for 10ms
// this will make the led blink at 0.5Hz (2 seconds on, 2 seconds off)

#define LED_BUILTIN 2 // ESP32 GPIO2

#define SECOND_TO_TICK(x) ((x * 1000) / portTICK_PERIOD_MS)
#define VTASK_DELAY_SECOND(x) (vTaskDelay(SECOND_TO_TICK(x)))

// global counter
volatile uint32_t counter = 0; // volatile because it's used by multiple tasks

// task 1
void task1(void *pvParameters)
{
    while (true)
    {
        counter++;
        VTASK_DELAY_SECOND(1); // 1 second
    }
}

// task 2
void task2(void *pvParameters)
{
    bool ledState = false; // false = LOW, true = HIGH
    while (true)
    {
        // toggle the led once every 2 seconds
        bool nextLedState = (counter % 4 < 2);
        if (ledState != nextLedState)
        {
            ledState = nextLedState;
            digitalWrite(LED_BUILTIN, ledState);
        }
        VTASK_DELAY_SECOND(0.1); // check every 100ms
    }
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT); // initialize LED_BUILTIN as an output GPIO pin.

    // create the 2 tasks
    xTaskCreate(
        task1,   // Task function
        "Task1", // Task name
        10000,   // Stack size (bytes)
        NULL,    // Parameters
        1,       // Task priority
        NULL     // Task handle
    );

    xTaskCreate(
        task2,   // Task function
        "Task2", // Task name
        10000,   // Stack size (bytes)
        NULL,    // Parameters
        1,       // Task priority
        NULL     // Task handle
    );
}

void loop()
{
    // Empty. Things are done in Tasks.
}