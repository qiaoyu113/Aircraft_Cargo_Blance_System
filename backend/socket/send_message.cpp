// send_message.cpp
#include "send_message.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

MessageSender::MessageSender(websocket::stream<boost::asio::basic_stream_socket<boost::asio::ip::tcp>>& ws) : ws(ws) {}

void MessageSender::sendMessage(const std::string& action, const json& parameter) {
    json response;
    response["action"] = action;
    response["parameter"] = parameter;
    // ws.write(net::buffer(response.dump()));
    ws.get().write(boost::asio::buffer(response.dump()));
}
