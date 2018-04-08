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
    // servo.attach(3);
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

    Serial.println((String)"R: " + rightDistance + (String)" cm");
    Serial.println((String)"M: " + middleDistance + (String)" cm");
    Serial.println((String)"L: " + leftDistance + (String)" cm");
    Serial.println((String)"Min: "
    + distance + (String)" cm");

    if(rightDistance > 30 && leftDistance > 30) {
      distance = middleDistance;
    }

    if (distance > 300) {
        forward(3000);
        return;
    } else if (distance > 200){
      forward(2000);
      return;
    } else if (distance > 180){
      forward(1800);
      return;
    } else if (distance > 160){
      forward(1600);
      return;
    } else if (distance > 140){
      forward(1400);
      return;
    } else if (distance > 120){
      forward(1200);
      return;
    } else if (distance > 100){
      forward(1000);
      return;
    } else if (distance > 80){
      forward(800);
      return;
    } else if (distance > 60){
      forward(600);
      return;
    } else if (distance > 40){
      forward(400);
      return;
    } else if (distance > 20){
      forward(200);
      return;
    }

    // if (distance > 20) {
    //     forward(200);
    //     return;
    // }

    servo.write(5);
    delay(1000);
    rightDistance = measureCm();
    servo.write(175);
    delay(1000);
    leftDistance = measureCm();

    int randNumber = random(150);
    if(rightDistance > 30 || leftDistance > 30){
      if(rightDistance > leftDistance) {
        right(150 + randNumber);
      } else {
        left(150 + randNumber);
      }
    } else {
      if(rightDistance > leftDistance) {
          back(1000);
          right(300 + randNumber);
      } else {
        back(1000);
        left(300 + randNumber);
      }
    }

    // if (rightDistance > 20) {
    //     right(200);
    // } else if (leftDistance > 20) {
    //     left(200);
    // } else {
    //     back(1000);
    //     left(300);
    // }
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
            forward(1000);
            break;
        case 'D':
            back(1000);
            break;
        case 'L':
            left(500);
            break;
        case 'R':
            right(500);
            break;
        case 'S':
            stop();
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
            servo.attach(3);
            exploration();
            break;
        case MANUAL:
            servo.detach();
            manual(command);
            break;
    }
}
