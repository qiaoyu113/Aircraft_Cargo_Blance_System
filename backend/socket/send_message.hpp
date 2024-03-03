// send_message.hpp

#ifndef SEND_MESSAGE_HPP
#define SEND_MESSAGE_HPP

#include <nlohmann/json.hpp>
#include <functional>
#include "websocket_session_main.hpp" // 包含WebSocketSession的定义

using json = nlohmann::json;

class MessageSender {
public:
    MessageSender(websocket::stream<tcp::socket>& ws);
    void sendMessage(const std::string& action, const json& parameter);

private:
    websocket::stream<tcp::socket>& ws;
};

#endif // SEND_MESSAGE_HPP
