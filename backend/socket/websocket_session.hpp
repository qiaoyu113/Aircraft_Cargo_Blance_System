// websocket_session.hpp

#pragma once

#include <boost/beast.hpp>
#include <iostream>

namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace websocket = boost::beast::websocket;

class WebSocketSession {
public:
    WebSocketSession(tcp::socket socket);

    void run();

private:
    int counter;

    int changeConveyorStatus(const std::string& parameter);

    tcp::socket socket;
    websocket::stream<tcp::socket> ws;
};
