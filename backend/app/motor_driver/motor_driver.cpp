/**
 * @file   motor_driver.cpp
 * @brief  Stepper motor execution file
 *
 * Implementation of the StepperMotor class that controls the movement of a
 * stepper motor using the GPIO pins on a Raspberry Pi.
 * int stepPin = 19; // STEP 
 * int dirPin = 17;  // DIR 
 * StepperMotor motor(stepPin, dirPin);
 * The starter motor moves forward
 * motor.startMoving(StepperMotor::DIR_FORWARD);
 * change direction
 * motor.startMoving(StepperMotor::DIR_BACKWARD);
 * stop stepping motor
 * motor.stop();
 *
 * @author Yuhan Liu
 * @date   2024-03-02
 */

#include "motor_driver.hpp"
#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include "../../socket/gpio_lock.hpp"


StepperMotor::StepperMotor(int stepPin, int dirPin) 
    : stepPin(stepPin), dirPin(dirPin), currentDirection(DIR_STOP) {
    if (gpioInitialise() < 0) {
        throw std::runtime_error("pigpio initialization failed");
    }
    gpioSetMode(this->stepPin, PI_OUTPUT);
    gpioSetMode(this->dirPin, PI_OUTPUT);
    motorThread = std::thread(&StepperMotor::runMotor, this, 500);
}

StepperMotor::~StepperMotor() {
    stop(); // Ensure the motor is stopped
    motorThread.join(); // Wait for the thread to finish
    // gpioTerminate();
}

void StepperMotor::startMoving(int direction) {
    setDirection(direction);
    if (direction != DIR_STOP) {
        // 启动电机
        runMotor(500); // Pass the appropriate delay parameters, or adjust them as needed
    }
}

void StepperMotor::stop() {
    setDirection(DIR_STOP);
}

void StepperMotor::setDirection(int direction) {
    currentDirection = direction;
}

void StepperMotor::runMotor(int delayUs) {
    auto startTime = std::chrono::steady_clock::now();
    while (true) {
        if (currentDirection == DIR_STOP) break;
        // std::lock_guard<std::mutex> lock(gpioMutex);
        gpioWrite(dirPin, currentDirection);
        gpioWrite(stepPin, 1);
        usleep(delayUs);
        gpioWrite(stepPin, 0);
        usleep(delayUs);

        // Calculate the time that has elapsed
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();

        // if 1 second has passed, exit the loop
        if (elapsedTime >= 500)
            break;
    }
}

int StepperMotor::getCurrentDirection() const {
    return currentDirection;
}