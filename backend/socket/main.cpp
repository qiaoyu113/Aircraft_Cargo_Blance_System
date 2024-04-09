/**
 * @file   main.cpp
 * @brief  main file for basic functions
 *
 * @author Yu Qiao
 * @date   2024-02-01
 *
 * Additional notes:
 * - ...
 */

// #include "websocket_session.hpp"
// #include "websocket_session_button.hpp"
#include "websocket_session_main.hpp"
#include <boost/asio.hpp>
#include <boost/asio/signal_set.hpp>
#include <iostream>
#include <thread>
// #include "../app/led_control/led.hpp"
// #include "../app/led_control/button.hpp"
#include "../app/controller/controller.hpp"

int main() {
    std::cerr << "main is comming" << std::endl;
    try {
        boost::asio::io_context ioc{1};
        boost::asio::signal_set signals(ioc, SIGINT, SIGTERM); // 监听SIGINT和SIGTERM信号
        signals.async_wait([&](const boost::system::error_code& /*error*/, int /*signal_number*/) {
            ioc.stop(); // 当捕获到信号时，停止io_context
        });

        tcp::acceptor acceptor{ioc, {boost::asio::ip::make_address("127.0.0.1"), 8022}};

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
