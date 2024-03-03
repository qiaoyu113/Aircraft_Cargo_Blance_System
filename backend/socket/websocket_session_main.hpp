// websocket_session_button.hpp

#ifndef WEBSOCKET_SESSION_MAIN_HPP
#define WEBSOCKET_SESSION_MAIN_HPP

#include <boost/beast.hpp>
#include <iostream>
#include "../app/controller/controller.hpp"
#include "send_message.hpp"

namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace websocket = boost::beast::websocket;

class WebSocketSession {
public:
    WebSocketSession(tcp::socket socket, Controller& controller);

    void run();

    void sendButtonState(bool pressed);

    void setButtonCallback(std::function<void(bool)> callback) {
        buttonCallback = callback;
    };

    // 新增发送消息的方法
    void sendMessage(const std::string& action, const json& parameter);

private:
    Controller& controller;
    tcp::socket socket;
    websocket::stream<tcp::socket> ws;
    std::function<void(bool)> buttonCallback;
    MessageSender messageSender; // 添加MessageSender成员变量
};

#endif // WEBSOCKET_SESSION_HPP
