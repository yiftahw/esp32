#include <Arduino.h>

#define LED_BUILTIN 2 // GPIO2

bool ledState = false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
    delay(500);
}