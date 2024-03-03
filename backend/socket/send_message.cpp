// send_message.cpp
#include "send_message.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

MessageSender::MessageSender(websocket::stream<tcp::socket>& ws) : ws(ws) {}

void MessageSender::sendMessage(const std::string& action, const json& parameter) {
    json response;
    response["action"] = action;
    response["parameter"] = parameter;
    ws.write(net::buffer(response.dump()));
}
