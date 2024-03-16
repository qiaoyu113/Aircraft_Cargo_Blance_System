/**
 * @file   websocket_session.cpp
 * @brief  socket session connection singleton file
 * 
 * @author Yu Qiao
 * @date   2024-02-10
 *
 * Additional notes:
 * - ...
 */

// websocket_session.cpp

#include "websocket_session.hpp"
#include "../app/conveyor_status/conveyor_status.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

WebSocketSession::WebSocketSession(tcp::socket socket)
    : socket(std::move(socket)), ws(std::move(this->socket)), counter(0) {}

void WebSocketSession::run() {
    try {
        // 在 run 方法中执行 accept
        std::cout << "Running WebSocketSession" << std::endl;
        // if (!socket.is_open()) {
        //     std::cerr << "Error: Socket is not open" << std::endl;
        //     return;
        // }
        
        ws.accept();

        for (;;) {
            boost::beast::flat_buffer buffer;
            ws.read(buffer);

            // 将接收到的消息转换为字符串
            std::string jsonString = boost::beast::buffers_to_string(buffer.data());
            std::cout << "message: " << jsonString << std::endl;

            try {
                // 解析 JSON 字符串为 JSON 对象
                json jsonObject = json::parse(jsonString);

                // 访问 JSON 对象的成员
                std::string action = jsonObject["action"];
                std::string parameter = jsonObject["parameter"];

                // 打印解析后的数据
                std::cout << "Action: " << action << std::endl;
                std::cout << "Parameter: " << parameter << std::endl;

                if(action == "changeConveyorStatus") {
                    // 根据接收到的消息来变更
                    int param = changeConveyorStatus(parameter);
                    // 发送更新后的值回客户端
                    json response;
                    response["action"] = action;
                    response["parameter"] = param;
                    ws.write(net::buffer(response.dump()));
                }

            } catch (const json::exception& e) {
                std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            }
        }

    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}