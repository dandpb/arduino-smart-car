/*
 *  * Blink
 *   * Turns on an LED on for one second,
 *    * then off for one second, repeatedly.
 *     */

#include "Arduino.h"

int in1 = 9;
int in2 = 8;
int in3 = 7;
int in4 = 6;
int ENA = 10;
int ENB = 5;

void forward() {
        digitalWrite(ENA, HIGH);
        digitalWrite(ENB, HIGH);
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        Serial.println("Forward");
}

void back() {
        digitalWrite(ENA, HIGH);
        digitalWrite(ENB, HIGH);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        Serial.println("Back");
}

void left() {
        digitalWrite(ENA, HIGH);
        digitalWrite(ENB, HIGH);
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        Serial.println("Left");
}

void right() {
        digitalWrite(ENA, HIGH);
        digitalWrite(ENB, HIGH);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        Serial.println("Right");
}

void setup() {
        pinMode(LED_BUILTIN, OUTPUT);

        Serial.begin(
            9600);  // Open the serial port and set the baud rate to 9600

        pinMode(in1, OUTPUT);
        pinMode(in2, OUTPUT);
        pinMode(in3, OUTPUT);
        pinMode(in4, OUTPUT);
        pinMode(ENA, OUTPUT);
        pinMode(ENB, OUTPUT);
}

void loop() {
        // forward();
        // delay(1000);
        // back();
        delay(1000);
        left();
        delay(1000);
        right();
        delay(1000);
}
