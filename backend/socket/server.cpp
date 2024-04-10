/**
 * @file   server.cpp
 * @brief  socket connection configuration file
 * 
 * @author Yu Qiao
 * @date   2024-02-10
 *
 * Additional notes:
 * - ...
 */

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <nlohmann/json.hpp>
#include "../app/conveyor_status/conveyor_status.hpp"

using json = nlohmann::json;

namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace websocket = boost::beast::websocket;

void websocket_session(tcp::socket socket) {
    try {
        websocket::stream<tcp::socket> ws{std::move(socket)};
        ws.accept();

        for(;;) {
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
                // std::cout << "Action: " << action << std::endl;
                // std::cout << "Parameter: " << parameter << std::endl;

                // 根据接收到的消息来增加或减少计数器
                int param = 0;
                if(action == "changeConveyorStatus") {
                    param = changeConveyorStatus(parameter);
                }
                // 发送更新后的计数器值回客户端
                json response;
                response["action"] = action;
                response["parameter"] = param;
                ws.write(net::buffer(response.dump()));

            } catch (const json::exception& e) {
                std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            }
        }

    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        net::io_context ioc{1};
        tcp::acceptor acceptor{ioc, {net::ip::make_address("127.0.0.1"), 8085}};
        
        for (;;) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);
            std::thread{websocket_session, std::move(socket)}.detach();
        }
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
