#include <Arduino.h>
#include <Movement.h>
#include <Led.h>

void setup() {
    Serial.begin(9600);
    setupMovement();
}

int incomingByte = 0;

void loop() {
    if (Serial.available() > 0) {
        incomingByte = Serial.read();
        switch (incomingByte) {
            case 'A':
                light(true);
                break;
            case 'B':
                light(false);
                break;
            case 'U':
                forward(100);
                break;
            case 'D':
                back(100);
                break;
            case 'L':
                left(100);
                break;
            case 'R':
                right(100);
                break;
            default:
                delay(100);
        }
    } else {
        delay(100);
    }
    // forward(1000);
    // stop(1000);
    // left(300);
    // stop(1000);
    // forward();
    // delay(1000);
    // back();
    // delay(1000);
    // left();
    // delay(1000);
    // right();
    // delay(1000);
}
