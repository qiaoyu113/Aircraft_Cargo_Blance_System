#include <iostream>
#include "button.hpp"
#include "led.hpp"

int main() {
    Button button;
    Led led;

    while (true) {
        if (button.isPressed()) {
            std::cout << "Button pressed" << std::endl;
            led.turnOn();
        } else {
            std::cout << "Button not pressed" << std::endl;
            led.turnOff();
        }
    }

    return 0;
}