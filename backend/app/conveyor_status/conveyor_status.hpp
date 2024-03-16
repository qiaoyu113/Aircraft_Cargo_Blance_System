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

// ConveyorStatus.hpp

#ifndef CONVEYOR_STATUS_HPP
#define CONVEYOR_STATUS_HPP

#include "../../socket/send_message.hpp"

class ConveyorStatus {
public:
    ConveyorStatus(); // 不需要 MessageSender 参数的构造函数
    void changeConveyorStatus(int parameter);

private:
    MessageSender messageSender; 
    int lastCounter = 0; 
};

#endif // CONVEYOR_STATUS_HPP
