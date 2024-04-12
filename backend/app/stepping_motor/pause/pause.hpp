/**
 * @file   pause.hpp
 * @brief  Header for stepper motor driver functionality
 *
 * Control the motor 
 *
 * @author Yuhan Liu
 * @date   2024-03-05
 */

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