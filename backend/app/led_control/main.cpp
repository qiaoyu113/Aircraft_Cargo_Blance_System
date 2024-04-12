// #include <iostream>
// #include "button.hpp"
// #include "led.hpp"

// int main() {
//     Button button;
//     Led led;

//     while (true) {
//         if (button.isPressed()) {
//             std::cout << "Button pressed" << std::endl;
//             led.turnOn();
//         } else {
//             std::cout << "Button not pressed" << std::endl;
//             led.turnOff();
//         }
//     }

//     return 0;
// }

// main.cpp


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
            // 在这里通过WebSocket发送更新给前端
            webSocket.sendButtonState(true);
        } else {
            std::cout << "真实按钮未按下" << std::endl;
            // 在这里通过WebSocket发送更新给前端
            webSocket.sendButtonState(false);
        }
    });

    Led led;

    while (true) {
        // 在这里可以执行其他逻辑
        if (button.isPressed()) {
            led.turnOn();
        } else {
            led.turnOff();
        }
    }

    return 0;
}
