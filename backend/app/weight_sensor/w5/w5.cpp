#include "button.hpp"
#include <wiringPi.h>
#include <iostream>

W5::w5(int pin) : pin(pin) {
    pin = 0; // GPIO7
    wiringPiSetup();
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_UP);
}

void W5::setCallback(std::function<void(bool)> callback) {
    this->callback = callback;
}

bool W5::weightReading() {
    bool pressed = digitalRead(pin) == HIGH;
    // std::cout << "isPressed in button" << (pressed ? "PRESSED" : "NOT PRESSED") << std::endl;
    
    if (callback) {
        std::cout << "into callback" << std::endl;
        callback(pressed);
    }

    return pressed;
}
