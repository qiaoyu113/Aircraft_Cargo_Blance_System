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
