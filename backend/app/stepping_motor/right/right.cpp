#include "right.hpp"
#include <wiringPi.h>

Right::Right(int pin) : pin(pin) {
    wiringPiSetup();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); // Turn off initially
}

void Right::turnOn() {
    digitalWrite(pin, HIGH);
    conveyorStatus.changeConveyorStatus(1); // 使用ConveyorStatus对象
}

void Right::turnOff() {
    digitalWrite(pin, LOW);
    conveyorStatus.changeConveyorStatus(0); // 使用ConveyorStatus对象
}
