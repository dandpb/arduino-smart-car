#include <Arduino.h>
#include <Movement.h>

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    setupMovement();
}

void loop() {
    forward(1000);
    stop(1000);
    left(300);
    stop(1000);
    // forward();
    // delay(1000);
    // back();
    // delay(1000);
    // left();
    // delay(1000);
    // right();
    // delay(1000);
}
