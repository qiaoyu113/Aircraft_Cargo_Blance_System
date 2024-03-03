#include "left.hpp"
#include <wiringPi.h>

Left::Left(int pin) : pin(pin) {
    wiringPiSetup();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); // Turn off initially
}

void Left::turnOn() {
    digitalWrite(pin, HIGH);
    conveyorStatus.changeConveyorStatus(1); // Use ConveyorStatus object
}

void Left::turnOff() {
    digitalWrite(pin, LOW);
    conveyorStatus.changeConveyorStatus(0); // 使用ConveyorStatus对象
}
