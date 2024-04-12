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

            // Converts the received message to a string
            std::string jsonString = boost::beast::buffers_to_string(buffer.data());
            std::cout << "message: " << jsonString << std::endl;

            try {
                // Parse JSON strings as JSON objects
                json jsonObject = json::parse(jsonString);

                // Access the members of the JSON object
                std::string action = jsonObject["action"];
                std::string parameter = jsonObject["parameter"];

                // Print the parsed data
                std::cout << "Action: " << action << std::endl;
                std::cout << "Parameter: " << parameter << std::endl;

                if(action == "changeConveyorStatus") {
                    int param = changeConveyorStatus(parameter);
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