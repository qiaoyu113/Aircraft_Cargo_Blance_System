#include "right.hpp"
// #include <wiringPi.h>
#include <pigpio.h>

Right::Right(int pin) : pin(pin) {
    // wiringPiSetup();
    // pinMode(pin, OUTPUT);
    // digitalWrite(pin, LOW); // Turn off initially
    if (gpioInitialise() < 0) {
        std::cerr << "pigpio initialization failed." << std::endl;
        return 1;
    }
    gpioSetMode(pin, PI_OUTPUT);
    gpioWrite(pin, PI_LOW);
}

void Right::turnOn() {
    // digitalWrite(pin, HIGH);
    gpioWrite(pin, PI_HIGH);
    conveyorStatus.changeConveyorStatus(1); // 使用ConveyorStatus对象
}

void Right::turnOff() {
    // digitalWrite(pin, LOW);
    gpioWrite(pin, PI_LOW);
    conveyorStatus.changeConveyorStatus(0); // 使用ConveyorStatus对象
}
