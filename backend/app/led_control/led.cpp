#include "led.hpp"
#include <wiringPi.h>

Led::Led() {
    pin = 7; // GPIO0
    wiringPiSetup();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); // Turn off initially
}

void Led::turnOn() {
    digitalWrite(pin, HIGH);
}

void Led::turnOff() {
<<<<<<< HEAD
    digitalWrite(pin, HIGH);
}
=======
    digitalWrite(pin, LOW);
}
>>>>>>> origin/main
