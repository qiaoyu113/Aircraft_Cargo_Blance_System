#ifndef RIGHT_HPP
#define RIGHT_HPP

#include "../../conveyor_status/conveyor_status.hpp"

class Right {
public:
    Right(int pin);
    void turnOn();
    void turnOff();
private:
    int pin;
    ConveyorStatus conveyorStatus;
};

#endif // RIGHT_HPP