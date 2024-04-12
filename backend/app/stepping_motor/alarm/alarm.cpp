/**
 * @file   alarm.cpp
 * @brief  Header for stepper motor driver functionality
 *
 * Control the motor and issue a warning signal
 *
 * @author Yuhan Liu
 * @date   2024-03-05
 */

#include "alarm.hpp"
#include <wiringPi.h>

Alarm::Alarm(int pin) : pin(pin) { // Initialize pin number
    wiringPiSetup();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); // Turn off initially
}

void Alarm::turnOn() {
    digitalWrite(pin, HIGH);
}

void Alarm::turnOff() {
    digitalWrite(pin, LOW);
}