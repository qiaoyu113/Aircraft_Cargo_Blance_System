#ifndef LEFT_HPP
#define LEFT_HPP

#include "../../conveyor_status/conveyor_status.hpp"
#include "../../../../socket/send_message.hpp"

class Left {
public:
    Left(int pin);
    void turnOn(MessageSender& messageSender); 
    void turnOff();
private:
    int pin;
    ConveyorStatus conveyorStatus;
    bool initialized = false;
};

#endif // LEFT_HPP