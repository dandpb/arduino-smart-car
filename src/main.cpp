#include <Arduino.h>
#include <Movement.h>
#include <Led.h>
#include <Servo.h>
#include <Ultrasonic.h>

#define EXPLORATION 0
#define MANUAL 1

Servo servo;
int mode = EXPLORATION;

void setup() {
    Serial.begin(9600);
    setupMovement();
    setupLed();
    setupUltrasonic();
    servo.attach(3);
}

void exploration() {
    int rightDistance = 0, leftDistance = 0, middleDistance = 0;
    servo.write(90);
    delay(500);
    middleDistance = measureCm();
    servo.write(45);
    delay(500);
    leftDistance = measureCm();
    servo.write(135);
    delay(500);
    rightDistance = measureCm();
    int distance = min(min(middleDistance, rightDistance), leftDistance);
    if (distance > 20) {
        forward(200);
        return;
    }
    servo.write(5);
    delay(1000);
    rightDistance = measureCm();
    servo.write(175);
    delay(1000);
    leftDistance = measureCm();
    if (rightDistance > 20) {
        right(200);
    } else if (leftDistance > 20) {
        left(200);
    } else {
        back(1000);
        right(300);
    }
}

void manual(int command) {
    switch (command) {
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
        case 'E':
            mode = EXPLORATION;
            break;
    }
}


void loop() {
    int command = 0;
    if (Serial.available() > 0) {
        command = Serial.read();
        mode = MANUAL;
    }
    switch (mode) {
        case EXPLORATION:
            exploration();
            break;
        case MANUAL:
            manual(command);
            break;
    }
}
