// send_message.hpp

#ifndef SEND_MESSAGE_HPP
#define SEND_MESSAGE_HPP

#include <boost/beast.hpp>
#include <nlohmann/json.hpp>
#include <functional>
#include "websocket_session_main.hpp" // 包含WebSocketSession的定义

using json = nlohmann::json;
namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class MessageSender {
public:
    // 修改构造函数参数类型
    MessageSender(websocket::stream<boost::asio::basic_stream_socket<boost::asio::ip::tcp>>& ws);
    void sendMessage(const std::string& action, const json& parameter);

private:
    // 修改成员变量类型
    websocket::stream<boost::asio::basic_stream_socket<boost::asio::ip::tcp>> ws;
};


#endif // SEND_MESSAGE_HPP
