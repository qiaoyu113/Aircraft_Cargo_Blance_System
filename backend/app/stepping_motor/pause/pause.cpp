#include "pause.hpp"
// #include <wiringPi.h>
#include <pigpio.h>

Pause::Pause(int pin) : pin(pin) {
    // wiringPiSetup();
    // pinMode(pin, OUTPUT);
    // digitalWrite(pin, LOW); // Turn off initially
    if (gpioInitialise() < 0) {
        throw std::runtime_error("pigpio initialization failed");
    }
    gpioSetMode(pin, PI_OUTPUT);
    gpioWrite(pin, PI_LOW);
}

void Pause::turnOn() {
    // digitalWrite(pin, HIGH);
    gpioWrite(pin, PI_HIGH);
    conveyorStatus.changeConveyorStatus(1); // 使用ConveyorStatus对象
}

void Pause::turnOff() {
    // digitalWrite(pin, LOW);
    gpioWrite(pin, PI_LOW);
    conveyorStatus.changeConveyorStatus(0); // 使用ConveyorStatus对象
}
