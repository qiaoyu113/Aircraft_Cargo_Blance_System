#include "led.hpp"
#include <wiringPi.h>

Led::Led() {
    pin = 7; // GPIO0
    wiringPiSetup();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH); // Turn off initially
}

void Led::turnOn() {
    digitalWrite(pin, LOW);
}

void Led::turnOff() {
    digitalWrite(pin, HIGH);
}
