// counter_operations.cpp

#include "conveyor_status.hpp"
#include "../socket/websocket_session.hpp"

int counter = 0; // Define the counter variable

int WebSocketSession::changeConveyorStatus(const std::string& parameter) {
    if(parameter == "warning") {
        counter = 0;
    } else {
        counter = 1;
    }

    return counter;
}
