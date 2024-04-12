/**
 * @file   conveyor_status.cpp
 * @brief  Determine the status of the conveyor belt and send it to the server
 *
 * @author Yu Qiao
 * @date   2024-02-26
 *
 * Additional notes:
 * - ...
 */

// conveyor_status.cpp
#include "conveyor_status.hpp"

ConveyorStatus::ConveyorStatus() {}

void ConveyorStatus::changeConveyorStatus(int parameter) { // Add a void return type
    int newCounter = parameter;

    // The send logic is executed only if the value of newCounter differs from lastCounter
    if (newCounter != lastCounter) {
        auto& messageSender = MessageSender::getInstance();
        messageSender.sendMessage("conveyorStatus", newCounter);

        lastCounter = newCounter; // Update lastCounter to its current value of newCounter
    }
}
