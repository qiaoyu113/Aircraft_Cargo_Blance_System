// main.cpp

// #include "websocket_session.hpp"
// #include "websocket_session_button.hpp"
#include "websocket_session_main.hpp"
#include <boost/asio.hpp>
#include <thread>
// #include "../app/led_control/led.hpp"
// #include "../app/led_control/button.hpp"
#include "../app/controller/controller.hpp"

int main() {
    std::cerr << "main is comming" << std::endl;
    try {
        boost::asio::io_context ioc{1};
        tcp::acceptor acceptor{ioc, {net::ip::make_address("127.0.0.1"), 8090}};

        for (;;) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);

            std::thread{[socket = std::move(socket)]() mutable {
                // 模拟电灯
                // WebSocketSession(std::move(socket)).run();
                // 真实电灯
                // Led led;  // 创建 Led 对象
                // Button button;  // 创建 Button 对象
                // WebSocketSession(std::move(socket), led, button).run();
                Controller controller;

                std::cerr << "main is comming" << std::endl;

                WebSocketSession(std::move(socket), controller).run();
            }}.detach();
        }

    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
