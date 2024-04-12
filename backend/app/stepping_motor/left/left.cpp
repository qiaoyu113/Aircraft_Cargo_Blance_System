#include "left.hpp"
// #include <wiringPi.h>
#include <pigpio.h>
#include <wiringPi.h>

Left::Left(int pin) : pin(pin) {
    // wiringPiSetup();
    // pinMode(pin, OUTPUT);
    // digitalWrite(pin, LOW); 
    if (gpioInitialise() < 0) {
        throw std::runtime_error("pigpio initialization failed");
    }
    gpioSetMode(pin, PI_OUTPUT);
    gpioWrite(pin, PI_LOW);
}

void Left::turnOn() {
    // digitalWrite(pin, HIGH);
    gpioWrite(pin, PI_HIGH);
    conveyorStatus.changeConveyorStatus(1); // Use ConveyorStatus object
}

void Left::turnOff() {
    // digitalWrite(pin, LOW);
    gpioWrite(pin, PI_LOW);
    conveyorStatus.changeConveyorStatus(0); // 使用ConveyorStatus对象
}
