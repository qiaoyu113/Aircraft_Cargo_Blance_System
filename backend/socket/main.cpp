// main.cpp

#include "websocket_session.hpp"
#include <boost/asio.hpp>
#include <thread>

int main() {
    try {
        boost::asio::io_context ioc{1};
        tcp::acceptor acceptor{ioc, {net::ip::make_address("127.0.0.1"), 8095}};

        for (;;) {
            tcp::socket socket{ioc};
            acceptor.accept(socket);

            // 在新线程中执行 WebSocket 逻辑
            std::thread{[socket = std::move(socket)]() mutable {
                WebSocketSession(std::move(socket)).run();
            }}.detach();
        }

    } catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
