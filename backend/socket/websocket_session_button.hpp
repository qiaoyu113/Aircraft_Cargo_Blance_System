// websocket_session_button.hpp

#ifndef WEBSOCKET_SESSION_HPP
#define WEBSOCKET_SESSION_HPP

#include <boost/beast.hpp>
#include <iostream>
#include "../app/led_control/led.hpp"
#include "../app/led_control/button.hpp"

namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace websocket = boost::beast::websocket;

class WebSocketSession {
public:
    WebSocketSession(tcp::socket socket, Led& led, Button& button);

    void run();

    void sendButtonState(bool pressed);

    void setButtonCallback(std::function<void(bool)> callback) {
        buttonCallback = callback;
    };

private:
    int counter;
    Led& led;
    Button& button;
    tcp::socket socket;
    websocket::stream<tcp::socket> ws;
    std::function<void(bool)> buttonCallback;
};

#endif // WEBSOCKET_SESSION_HPP
