/**
 * @file   led.cpp
 * @brief  Led executive file
 *
 * @author Yu Qiao
 * @date   2024-02-02
 *
 * Additional notes:
 * - ...
 */

#include "led.hpp"
#include <wiringPi.h>

Led::Led() {
    pin = 7; // GPIO0
    wiringPiSetup();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); // Turn off initially
}

void Led::turnOn() {
    digitalWrite(pin, HIGH);
}

void Led::turnOff() {
    digitalWrite(pin, LOW);
}
