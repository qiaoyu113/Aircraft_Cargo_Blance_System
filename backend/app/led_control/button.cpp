#include "button.hpp"
#include <wiringPi.h>

Button::Button() {
    pin = 0; // GPIO7
    wiringPiSetup();
    pinMode(pin, INPUT);
    pullUpDnControl(pin, PUD_UP);
}

bool Button::isPressed() {
    return digitalRead(pin) == LOW;
}