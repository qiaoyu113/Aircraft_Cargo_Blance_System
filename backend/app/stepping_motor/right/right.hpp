/**
 * @file   right.hpp
 * @brief  Header for stepper motor driver functionality
 *
 * Control the motor 
 *
 * @author Yuhan Liu
 * @date   2024-03-05
 */

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