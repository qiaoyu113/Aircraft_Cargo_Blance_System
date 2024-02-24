// websocket_session_button.hpp

#ifndef WEBSOCKET_SESSION_MAIN_HPP
#define WEBSOCKET_SESSION_MAIN_HPP

#include <boost/beast.hpp>
#include <iostream>
#include "../app/controller/controller.hpp"
#include "../app/controller/controller.hpp"

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

private:
    Controller& controller;
    tcp::socket socket;
    websocket::stream<tcp::socket> ws;
    std::function<void(bool)> buttonCallback;
};

#endif // WEBSOCKET_SESSION_HPP
