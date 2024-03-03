#ifndef PAUSE_HPP
#define PAUSE_HPP

#include "../../conveyor_status/conveyor_status.hpp"

class Pause {
public:
    Pause(int pin);
    void turnOn();
    void turnOff();
private:
    int pin;
    ConveyorStatus conveyorStatus;
};

#endif // PAUSE_HPP