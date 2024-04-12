/**
 * @file   left.hpp
 * @brief  Header for stepper motor driver functionality
 *
 * Control the motor 
 *
 * @author Yuhan Liu
 * @date   2024-03-05
 */

#ifndef LEFT_HPP
#define LEFT_HPP

#include "../../conveyor_status/conveyor_status.hpp"

class Left {
public:
    Left(int pin);
    void turnOn(); 
    void turnOff();
private:
    int pin;
    ConveyorStatus conveyorStatus;
};

#endif // LEFT_HPP