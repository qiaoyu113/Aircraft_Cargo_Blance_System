#include "right.hpp"
#include <wiringPi.h>

Right::Right(int pin) : pin(pin) {
    wiringPiSetup();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); // Turn off initially
}

void Right::turnOn() {
    digitalWrite(pin, HIGH);
}

void Right::turnOff() {
    digitalWrite(pin, LOW);
}
