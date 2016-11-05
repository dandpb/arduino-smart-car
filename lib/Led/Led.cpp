#include <Led.h>
#include <Arduino.h>

int LED=13;

void setupLed() {
    pinMode(LED, OUTPUT);
}

void light(bool on) {
    digitalWrite(LED, on ? HIGH : LOW);
}
