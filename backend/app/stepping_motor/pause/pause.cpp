#include "pause.hpp"
#include <wiringPi.h>

Pause::Pause(int pin) : pin(pin) {
    wiringPiSetup();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); // Turn off initially
}

void Pause::turnOn() {
    digitalWrite(pin, HIGH);
    conveyorStatus.changeConveyorStatus(1); // 使用ConveyorStatus对象
}

void Pause::turnOff() {
    digitalWrite(pin, LOW);
    conveyorStatus.changeConveyorStatus(0); // 使用ConveyorStatus对象
}
