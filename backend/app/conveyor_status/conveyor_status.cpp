// counter_operations.cpp
#include <nlohmann/json.hpp>
#include "conveyor_status.hpp"
#include "../../socket/websocket_session.hpp"

int counter = 0; // Define the counter variable

int WebSocketSession::changeConveyorStatus(const std::string& parameter) {
    json response;
    if(parameter == 0) {
        counter = 0;
    } else {
        counter = 1;
    }

    response["action"] = 'conveyorStatus';
    response["parameter"] = counter;
    ws.write(net::buffer(response.dump()));
}
