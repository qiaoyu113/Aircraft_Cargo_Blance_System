#include "w1.hpp"
#include <wiringPi.h>
#include <iostream>

W1::W1(int pin) : pin(pin) {
    wiringPiSetup();
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_UP);
}

void W1::setCallback(std::function<void(bool)> callback) {
    this->callback = callback;
}

bool W1::weightReading() {
    bool pressed = digitalRead(pin) == HIGH;
    // std::cout << "isPressed in button" << (pressed ? "PRESSED" : "NOT PRESSED") << std::endl;
    
    if (callback) {
        std::cout << "into callback" << std::endl;
        callback(pressed);
    }

    return pressed;
}
