/**
 * @file   motor_driver.hpp
 * @brief  Header for stepper motor driver functionality
 *
 * This file declares the StepperMotor class and its interface for controlling
 * a stepper motor using GPIO pins. It is designed to be used with the pigpio
 * library on a Raspberry Pi.
 *
 * @author Yuhan Liu
 * @date   2024-03-02
 */

#ifndef MOTOR_DRIVER_HPP
#define MOTOR_DRIVER_HPP

#include <thread>
#include <iostream>
#include <pigpio.h>
#include <unistd.h>

class StepperMotor {
public:
    StepperMotor(int stepPin, int dirPin); // Constructor
    ~StepperMotor(); // Destructor
    
    void startMoving(int direction); // Start the motor
    void stop(); // Stop the motor
    int getCurrentDirection() const;
    
    // Direction constants
    static const int DIR_FORWARD = PI_HIGH;
    static const int DIR_BACKWARD = PI_LOW;
    static const int DIR_STOP = -1;

private:
    const int stepPin;
    const int dirPin;

    // Current direction of the motor
    volatile int currentDirection;

    std::thread motorThread;

    void runMotor(int delayUs); // Method used internally for the motor thread
    void setDirection(int direction); // Set the motor direction
};

#endif // MOTOR_DRIVER_HPP
