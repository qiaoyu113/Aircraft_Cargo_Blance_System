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

#include "button.hpp"
#include <wiringPi.h>

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
    bool pressed = digitalRead(pin) == LOW;
    
    if (callback) {
        callback(pressed);
    }

    return pressed;
}
