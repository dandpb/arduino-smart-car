#include <Arduino.h>
#include <Movement.h>
#include <Led.h>
#include <Servo.h>

Servo servo;

void setup() {
    Serial.begin(9600);
    setupMovement();
    setupLed();
    servo.attach(3);
    servo.write(90);
}

void loop() {
    servo.write(90);
    delay(1000);
    servo.write(135);
    delay(1000);
    servo.write(45);
    delay(1000);
    
    //if (Serial.available() > 0) {
        //int incomingByte = Serial.read();
        //switch (incomingByte) {
            //case 'A':
                //light(true);
                //break;
            //case 'B':
                //light(false);
                //break;
            //case 'U':
                //forward(100);
                //break;
            //case 'D':
                //back(100);
                //break;
            //case 'L':
                //left(100);
                //break;
            //case 'R':
                //right(100);
                //break;
            //default:
                //delay(100);
        //}
    //} else {
        //delay(100);
    //}
}
