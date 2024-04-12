/**
 * @file   led.cpp
 * @brief  Light the light to execute the file
 * 
 * @author Yu Qiao
 * @date   2024-02-02
 *
 * Additional notes:
 * - ...
 */

// main.cpp
#include <iostream>
#include "button.hpp"
#include "led.hpp"
#include "websocket_session_button.hpp"

int main() {
    WebSocketSession webSocket;

    Button button;
    button.setCallback([&webSocket](bool pressed) {
        if (pressed) {
            std::cout << "真实按钮按下" << std::endl;
            // This is where updates are sent to the frontend via WebSocket
            webSocket.sendButtonState(true);
        } else {
            std::cout << "真实按钮未按下" << std::endl;
            // This is where updates are sent to the frontend via WebSocket
            webSocket.sendButtonState(false);
        }
    });

    Led led;

    while (true) {
        // Other logic can be performed here
        if (button.isPressed()) {
            led.turnOn();
        } else {
            led.turnOff();
        }
    }

    return 0;
}
