// websocket_session_button.cpp
#include "websocket_session_main.hpp"
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>

using json = nlohmann::json;

WebSocketSession::WebSocketSession(tcp::socket socket, Controller& controller)
    : controller(controller), socket(std::move(socket)), ws(std::move(this->socket)), messageSender() {
        // 初始化MessageSender
        // messageSender.initialize(std::move(this->socket));
    }


void WebSocketSession::run() {
    try {
        std::cout << "Running WebSocketSession" << std::endl;
        ws.accept();

        // 设置MessageSender的发送函数
        auto& ms = MessageSender::getInstance();
        ms.setSendFunction([this](const std::string& message) {
            if(ws.is_open()) {
                ws.write(boost::asio::buffer(message));
            }
        });

        std::vector<double> lastWeight; // 新增变量记录上一次的重量

        for (;;) {
            std::vector<double> currentWeight = controller.readWeight();

            // 检查当前的重量和上一次的重量是否相同
            bool weightChanged = (currentWeight != lastWeight);
            lastWeight = currentWeight; // 更新上一次的重量

            // 检查是否至少有一个重量读数非零
            bool hasValue = false;
            for (double weight : currentWeight) {
                if (weight > 0) { // 假设"有值"意味着重量大于0
                    hasValue = true;
                    break;
                }
            }

            // 如果重量发生变化且至少有一个重量读数非零，进入if判断
            // if (weightChanged && hasValue) {
            if (hasValue) {
                std::cout << "Detected weights: ";
                for (double weight : currentWeight) {
                    std::cout << weight << " ";
                }
                std::cout << std::endl;
                // 传值传感器到前端
                json response;
                response["action"] = "visualization";
                response["parameter"] = currentWeight;
                ws.write(net::buffer(response.dump()));
                // 如果有重量，调用real-time processing进行逻辑处理
                controller.RTP(currentWeight);
            } else {
                controller.TurnOff();
                std::cout << "No weights detected or weights are unchanged." << std::endl;
            }

            // 可以在这里添加一个短暂的延时来减少CPU的使用
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

    } catch (std::exception const& e) {
        std::cerr << "错误：" << e.what() << std::endl;
    }
}

void WebSocketSession::sendMessage(const std::string& action, const json& parameter) {
    messageSender.sendMessage(action, parameter);
}