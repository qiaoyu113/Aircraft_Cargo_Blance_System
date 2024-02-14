#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>

namespace net = boost::asio;
using tcp = net::ip::tcp;
namespace websocket = boost::beast::websocket;

void websocket_session(tcp::socket socket) {
    try {
        websocket::stream<tcp::socket> ws{std::move(socket)};
        ws.accept();

        int counter = 0; // 定义一个计数器

        for(;;) {
            boost::beast::flat_buffer buffer;
            ws.read(buffer);

            // 将接收到的消息转换为字符串
            std::string message = boost::beast::buffers_to_string(buffer.data());

            // 根据接收到的消息来增加或减少计数器
            if(message == "increase") {
                ++counter;
            } else if(message == "decrease") {
                --counter;
            }

            // 发送更新后的计数器值回客户端
            ws.write(net::buffer(std::to_string(counter)));
        }

    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        net::io_context ioc{1};
        tcp::acceptor acceptor{ioc, {net::ip::make_address("127.0.0.1"), 8084}};
        
        for (;;) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);
            std::thread{websocket_session, std::move(socket)}.detach();
        }
    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
