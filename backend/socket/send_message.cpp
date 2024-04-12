/**
 * @file   send_message.cpp
 * @brief  It is responsible for sending the reading of the gravity sensor to the remote server through the socket in real time
 *
 * @author Yu Qiao
 * @date   2024-02-12
 *
 * Additional notes:
 * - ...
 */

// send_message.cpp
#include "send_message.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;
namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

MessageSender::MessageSender() {}

// void MessageSender::initialize(tcp::socket&& socket) {
//     ws = std::make_unique<websocket::stream<tcp::socket>>(std::move(socket));
// }

void MessageSender::setSendFunction(const std::function<void(const std::string&)>& sendFunction) {
    // std::cout << "setSendFunction"<< std::endl;
    this->sendFunction = sendFunction;
}

void MessageSender::sendMessage(const std::string& action, const json& parameter) {
    // if (!ws) {
    //     throw std::runtime_error("WebSocket stream not initialized.");
    // }
    if (!sendFunction) {
        throw std::runtime_error("Send function not set.");
    }

    json response;
    response["action"] = action;
    response["parameter"] = parameter;
    // ws.write(net::buffer(response.dump()));

    // ws.get().write(boost::asio::buffer(response.dump()));
    sendFunction(response.dump());
}

MessageSender& MessageSender::getInstance() {
    static MessageSender instance;
    return instance;
}
