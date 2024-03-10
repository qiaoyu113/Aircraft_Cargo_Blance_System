#include "w3.hpp"
// #include <wiringPi.h>
#include <pigpio.h>
#include <iostream>

W3::W3(int pin) : pin(pin) {
    // wiringPiSetup();
    if (gpioInitialise() < 0) {
        throw std::runtime_error("pigpio initialization failed");
    }
    // pinMode(pin, INPUT);
    // pullUpDnControl(pin, PUD_DOWN);
    gpioSetMode(pin, PI_INPUT);
    gpioSetPullUpDown(pin, PI_PUD_DOWN);
}

void W3::setCallback(std::function<void(bool)> callback) {
    this->callback = callback;
}

bool W3::weightReading() {
    // bool pressed = digitalRead(pin) == HIGH;
    bool pressed = gpioRead(pin) == PI_HIGH;
    // std::cout << "isPressed in button" << (pressed ? "PRESSED" : "NOT PRESSED") << std::endl;
    
    if (callback) {
        std::cout << "into callback" << std::endl;
        callback(pressed);
    }

    return pressed;
}
