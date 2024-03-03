#ifndef LEFT_HPP
#define LEFT_HPP

#include "../../conveyor_status/conveyor_status.hpp"

class Left {
public:
    Left(int pin); // Constructor now takes a pin number
    void turnOn();
    void turnOff();
private:
    int pin;
    ConveyorStatus conveyorStatus;
};

#endif // LEFT_HPP