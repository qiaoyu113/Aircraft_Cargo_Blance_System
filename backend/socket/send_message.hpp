/**
 * @file   send_message.hpp
 * @brief  It is responsible for sending the reading of the gravity sensor to the remote server through the socket in real time
 *
 * @author Yu Qiao
 * @date   2024-02-12
 *
 * Additional notes:
 * - ...
 */

#ifndef SEND_MESSAGE_HPP
#define SEND_MESSAGE_HPP

#include <boost/beast.hpp>
#include <nlohmann/json.hpp>
#include <functional>
#include <iostream>
#include <memory>

using json = nlohmann::json;
namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class MessageSender {
public:
    // 默认构造函数
    MessageSender();
    void sendMessage(const std::string& action, const json& parameter);
    void setSendFunction(const std::function<void(const std::string&)>& sendFunction);
    // 初始化函数，确保在使用前正确初始化websocket
    void initialize(tcp::socket&& socket);

    static MessageSender& getInstance();

private:
    // 修改成员变量类型
    // std::reference_wrapper<websocket::stream<boost::asio::ip::tcp::socket>> ws; // 使用reference_wrapper包装引用
    std::function<void(const std::string&)> sendFunction;
};


#endif // SEND_MESSAGE_HPP
