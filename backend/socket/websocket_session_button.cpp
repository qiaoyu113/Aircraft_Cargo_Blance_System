/**
 * @file   websocket_session_button.cpp
 * @brief  The main file executed by the gravity sensor is simulated by the button
 * 
 * @author Yu Qiao
 * @date   2024-02-03
 *
 * Additional notes:
 * - ...
 */


// websocket_session_button.cpp
#include "websocket_session_button.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

WebSocketSession::WebSocketSession(tcp::socket socket, Led& led, Button& button)
    : led(led), button(button), socket(std::move(socket)), ws(std::move(this->socket)), counter(0) {}

void WebSocketSession::run() {
    try {
        std::cout << "Running WebSocketSession" << std::endl;
        ws.accept();

        bool lastButtonState = false; // 新增变量记录上一次按钮状态

        for (;;) {
            bool currentButtonState = button.isPressed(); // 当前的按钮状态

            // 只有在按钮状态发生改变时才处理
            if (currentButtonState != lastButtonState) {
                if (currentButtonState) {
                    // 按钮被按下
                    std::cout << "Button pressed, sending to web." << std::endl;
                    json buttonResponse;
                    buttonResponse["action"] = "button";
                    buttonResponse["parameter"] = true;
                    ws.write(net::buffer(buttonResponse.dump()));
                    led.turnOn();
                } else {
                    // 按钮被释放
                    led.turnOff();
                }

                lastButtonState = currentButtonState; // 更新按钮状态
            }

            // 可以在这里添加一个短暂的延时来减少CPU的使用
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

    } catch (std::exception const& e) {
        std::cerr << "错误：" << e.what() << std::endl;
    }
}
