#include <Arduino.h>
#include <Movement.h>

int IN1 = 7;
int IN2 = 8;
int IN3 = 9;
int IN4 = 11;
int ENA = 5;
int ENB = 6;

int carSpeed = 200;

void setupMovement() {
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
}

void forward(int time) {
    Serial.println("Forward");
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    delay(time);
    stop();
}

void back(int time) {
    Serial.println("Back");
    digitalWrite(ENA,HIGH);
    digitalWrite(ENB,HIGH);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(time);
    stop();
}

void left(int time) {
    Serial.println("Left");
    digitalWrite(ENA,HIGH);
    digitalWrite(ENB,HIGH);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
    delay(time);
    stop();
}

void right(int time) {
    Serial.println("Right");
    digitalWrite(ENA,HIGH);
    digitalWrite(ENB,HIGH);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(time);
    stop();
}

void stop() {
    Serial.println("Stop");
    digitalWrite(ENA,LOW);
    digitalWrite(ENB,LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void stop(int time) {
    Serial.println("Stop");
    digitalWrite(ENA,LOW);
    digitalWrite(ENB,LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(time);
}
