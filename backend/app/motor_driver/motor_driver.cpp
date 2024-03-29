/**
 * @file   motor_driver.cpp
 * @brief  Stepper motor execution file
 *
 * Implementation of the StepperMotor class that controls the movement of a
 * stepper motor using the GPIO pins on a Raspberry Pi.
 * int stepPin = 19; // STEP 引脚
 * int dirPin = 17;  // DIR 引脚
 * StepperMotor motor(stepPin, dirPin);
 * 启动电机向前移动
 * motor.startMoving(StepperMotor::DIR_FORWARD);
 * 改变方向
 * motor.startMoving(StepperMotor::DIR_BACKWARD);
 * 停止电机
 * motor.stop();
 *
 * @author Yuhan Liu
 * @date   2024-03-02
 */

#include "motor_driver.hpp"
#include <iostream>
#include <pigpio.h>
#include <unistd.h>

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
    gpioTerminate();
}

void StepperMotor::startMoving(int direction) {
    setDirection(direction);
}

void StepperMotor::stop() {
    setDirection(DIR_STOP);
}

void StepperMotor::setDirection(int direction) {
    currentDirection = direction;
}

void StepperMotor::runMotor(int delayUs) {
    while (true) {
        if (currentDirection == DIR_STOP) break;
        gpioWrite(dirPin, currentDirection);
        gpioWrite(stepPin, 1);
        usleep(delayUs);
        gpioWrite(stepPin, 0);
        usleep(delayUs);
    }
}

int StepperMotor::getCurrentDirection() const {
    return currentDirection;
}

// create an instance of StepperMotor and use its methods.
// 假设这是一个函数，在其他文件中
// void controlMotor() {
//     // 创建StepperMotor类的实例
//     // 假设你有两个GPIO引脚分别用于STEP和DIR
//     int stepPin = 19; // STEP 引脚
//     int dirPin = 17;  // DIR 引脚
//     StepperMotor motor(stepPin, dirPin);

//     // 启动电机向前移动
//     motor.startMoving(StepperMotor::DIR_FORWARD);
//     // 改变方向
//     motor.startMoving(StepperMotor::DIR_BACKWARD);
//     // 停止电机
//     motor.stop();
// }
