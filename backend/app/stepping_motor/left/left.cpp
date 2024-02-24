#include "left.hpp"
#include <wiringPi.h>

Left::Left(int pin) : pin(pin) { // Initialize pin number
    wiringPiSetup();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); // Turn off initially
}

void Left::turnOn() {
    digitalWrite(pin, HIGH);
}

void Left::turnOff() {
    digitalWrite(pin, LOW);
}
