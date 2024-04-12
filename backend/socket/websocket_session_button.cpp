/**
 * @file   websocket_session_button.cpp
 * @brief  The main file executed by the gravity sensor is simulated by the button
 * 
 * @author Yu Qiao
 * @date   2024-02-03
 *
 * Additional notes:
 * - ...
 */


// websocket_session_button.cpp
#include "websocket_session_button.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

WebSocketSession::WebSocketSession(tcp::socket socket, Led& led, Button& button)
    : led(led), button(button), socket(std::move(socket)), ws(std::move(this->socket)), counter(0) {}

void WebSocketSession::run() {
    try {
        std::cout << "Running WebSocketSession" << std::endl;
        ws.accept();

        bool lastButtonState = false; // New variable records the last button status

        for (;;) {
            bool currentButtonState = button.isPressed(); // Current button status

            // It is processed only when the button state changes
            if (currentButtonState != lastButtonState) {
                if (currentButtonState) {
                    // The button is pressed
                    std::cout << "Button pressed, sending to web." << std::endl;
                    json buttonResponse;
                    buttonResponse["action"] = "button";
                    buttonResponse["parameter"] = true;
                    ws.write(net::buffer(buttonResponse.dump()));
                    led.turnOn();
                } else {
                    // Button released
                    led.turnOff();
                }

                lastButtonState = currentButtonState; // Update button status
            }

            // add a short delay here to reduce CPU usage
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

    } catch (std::exception const& e) {
        std::cerr << "error" << e.what() << std::endl;
    }
}
