/**
 * @file   websocket_session_main.cpp
 * @brief  The final version of the main file for production use
 * 
 * @author Yu Qiao
 * @date   2024-02-20
 *
 * Additional notes:
 * - ...
 */

#include "websocket_session_main.hpp"
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>

using json = nlohmann::json;

WebSocketSession::WebSocketSession(tcp::socket socket, Controller& controller)
    : controller(controller), socket(std::move(socket)), ws(std::move(this->socket)), messageSender() {
        // initial MessageSender
        // messageSender.initialize(std::move(this->socket));
    }


void WebSocketSession::run() {
    try {
        std::cout << "Running WebSocketSession" << std::endl;
        ws.accept();

        // Set the sending function of MessageSender
        auto& ms = MessageSender::getInstance();
        ms.setSendFunction([this](const std::string& message) {
            if(ws.is_open()) {
                ws.write(boost::asio::buffer(message));
            }
        });

        std::vector<int> lastWeight; // New variable records the last weight

        // Set the callback function for controller
        controller.setCallback([this](bool weightDetected, const std::vector<int>& currentWeight) {
            if (weightDetected) {
                // std::cout << "Weight detected." << std::endl;
                // Build a JSON response and send it via WebSocket
                json response = {
                    {"action", "visualization"},
                    {"parameter", currentWeight}
                };
                ws.write(boost::asio::buffer(response.dump()));
                // Call real-time processing for logical processing
                controller.RTP(currentWeight);
                // controller.readWeight();
            }
        });

        controller.readWeight(); // Detects weight changes and may trigger callbacks

        // Infinite loops are used to keep the session active, but the actual weight change handling logic is taken care of by the callback function
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Simple latency to reduce CPU load
        }

    } catch (std::exception const& e) {
        std::cerr << "错误：" << e.what() << std::endl;
    }
}

void WebSocketSession::sendMessage(const std::string& action, const json& parameter) {
    messageSender.sendMessage(action, parameter);
}