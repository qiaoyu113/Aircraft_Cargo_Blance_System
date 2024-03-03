// websocket_session_button.cpp
#include "websocket_session_main.hpp"
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>

using json = nlohmann::json;

WebSocketSession::WebSocketSession(tcp::socket socket, Controller& controller)
    : controller(controller), socket(std::move(socket)), ws(std::move(this->socket)){}

void WebSocketSession::run() {
    try {
        std::cout << "Running WebSocketSession" << std::endl;
        ws.accept();

        bool lastButtonState = false; // 新增变量记录上一次按钮状态

        int param = 0; // 模拟计时
        int tt = 0;
        for (;;) {
            std::vector<double> currentWeight = controller.readWeight();

            // 检查是否至少有一个重量读数非零
            bool hasValue = false;
            for (double weight : currentWeight) {
                if (weight > 0) { // 假设"有值"意味着重量大于0
                    hasValue = true;
                    break;
                }
            }

            // 如果至少有一个重量读数非零，进入if判断
            if (hasValue) {
                std::cout << "Detected weights: ";
                for (double weight : currentWeight) {
                    std::cout << weight << " ";
                }
                std::cout << std::endl;

                // 如果有重量，调用real-time processing进行逻辑处理
                controller.RTP(currentWeight);
            } else {
                // controller.TurnOff();
                // std::cout << "No weights detected." << std::endl;
                if(param != tt) {
                    json response;
                    response["action"] = "w1";
                    response["parameter"] = tt;
                    ws.write(net::buffer(response.dump()));
                    param = tt;
                }
                tt++;
            }

            // 可以在这里添加一个短暂的延时来减少CPU的使用
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

    } catch (std::exception const& e) {
        std::cerr << "错误：" << e.what() << std::endl;
    }
}
