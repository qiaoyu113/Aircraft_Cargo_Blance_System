// #include "button.hpp"
// #include <wiringPi.h>

// Button::Button() {
//     pin = 0; // GPIO7
//     wiringPiSetup();
//     pinMode(pin, INPUT);
//     pullUpDnControl(pin, PUD_UP);
// }

// bool Button::isPressed() {
//     return digitalRead(pin) == LOW;
// }

// button.cpp

/**
 * @file   button.cpp
 * @brief  Button executive file
 *
 * @author Yuhan Liu
 * @date   2024-02-02
 *
 * Additional notes:
 * - ...
 */

#include "button.hpp"
#include <wiringPi.h>
#include <iostream>

Button::Button() {
    pin = 0; // GPIO7
    wiringPiSetup();
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_UP);
}

void Button::setCallback(std::function<void(bool)> callback) {
    this->callback = callback;
}

bool Button::isPressed() {
    bool pressed = digitalRead(pin) == HIGH;
    // std::cout << "isPressed in button" << (pressed ? "PRESSED" : "NOT PRESSED") << std::endl;
    
    if (callback) {
        std::cout << "into callback" << std::endl;
        callback(pressed);
    }

    return pressed;
}
