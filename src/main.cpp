#include <Arduino.h>
#include <Movement.h>
#include <Led.h>

void setup() {
    Serial.begin(9600);
    setupMovement();
}

bool led = false;

void loop() {
    light(true);
    delay(300);
    light(false);
    delay(100);

    //forward(1000);
    //stop(1000);
    //left(300);
    //stop(1000);
    // forward();
    // delay(1000);
    // back();
    // delay(1000);
    // left();
    // delay(1000);
    // right();
    // delay(1000);
}
