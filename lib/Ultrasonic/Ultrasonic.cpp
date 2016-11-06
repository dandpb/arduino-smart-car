#include <Arduino.h>

int Echo = A4;
int Trig = A5;

void setupUltrasonic() {
    pinMode(Echo, INPUT);
    pinMode(Trig, OUTPUT);
}

int measureCm() {
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(20);
    digitalWrite(Trig, LOW);
    float Fdistance = pulseIn(Echo, HIGH);
    Fdistance = Fdistance / 58;
    return (int)Fdistance;
}
