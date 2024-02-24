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

        for (;;) {
            // 处理真实按钮的回调
            if (button.isPressed()) {
                // 如果按钮按下，发送给前端按钮按下的状态
                bool isPressed = button.isPressed();
                std::cout << "is Pressed to web:" << isPressed << std::endl;
                json buttonResponse;
                buttonResponse["action"] = "button";
                buttonResponse["parameter"] = isPressed;
                ws.write(net::buffer(buttonResponse.dump()));
                // 在按钮按下时点灯
                led.turnOn();

            } else {
                // 如果按钮未按下，可以在这里执行熄灯的操作
                led.turnOff();
            }
        }

    } catch (std::exception const& e) {
        std::cerr << "错误：" << e.what() << std::endl;
    }
}
