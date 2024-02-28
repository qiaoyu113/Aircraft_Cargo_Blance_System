#include "pause.hpp"
#include <wiringPi.h>

Pause::Pause(int pin) : pin(pin) {
    wiringPiSetup();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); // Turn off initially
}

void Pause::turnOn() {
    digitalWrite(pin, HIGH);
}

void Pause::turnOff() {
    digitalWrite(pin, LOW);
}
