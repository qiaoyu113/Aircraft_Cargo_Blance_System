#include "w4.hpp"
#include <wiringPi.h>
#include <iostream>

W4::W4(int pin) : pin(pin) {
    wiringPiSetup();
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_DOWN);
}

void W4::setCallback(std::function<void(bool)> callback) {
    this->callback = callback;
}

bool W4::weightReading() {
    bool pressed = digitalRead(pin) == HIGH;
    // std::cout << "isPressed in button" << (pressed ? "PRESSED" : "NOT PRESSED") << std::endl;
    
    if (callback) {
        std::cout << "into callback" << std::endl;
        callback(pressed);
    }

    return pressed;
}
