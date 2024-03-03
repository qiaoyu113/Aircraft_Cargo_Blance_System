// ConveyorStatus.hpp

#ifndef CONVEYOR_STATUS_HPP
#define CONVEYOR_STATUS_HPP

#include "../../socket/send_message.hpp"

class ConveyorStatus {
public:
    ConveyorStatus(MessageSender& sender);
    void changeConveyorStatus(int parameter);

private:
    MessageSender& messageSender; 
    int lastCounter = 0; 
};

#endif // CONVEYOR_STATUS_HPP
