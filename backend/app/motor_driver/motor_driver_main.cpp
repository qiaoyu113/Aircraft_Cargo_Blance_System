/**
 * @file   motor_driver.cpp
 * @brief  Stepper motor execution file
 *
 * @author Yuhan Liu
 * @date   2024-03-02
 *
 * Additional notes:
 * - ...
 */

#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include <thread>

// Define STEP and DIR pins
const int stepPin = 19;
const int dirPin = 17;

// Define direction constants
const int DIR_FORWARD = PI_HIGH;
const int DIR_BACKWARD = PI_LOW;
const int DIR_STOP = -1; // Add a state representing stop

// Global variable for the current direction
volatile int currentDirection = DIR_STOP;

void stepMotor(int delayUs) {
    while (currentDirection != DIR_STOP) {
        if (currentDirection == DIR_FORWARD || currentDirection == DIR_BACKWARD) {
            gpioWrite(dirPin, currentDirection);
            gpioWrite(stepPin, 1);
            usleep(delayUs);
            gpioWrite(stepPin, 0);
            usleep(delayUs);
        }
    }
}

void setDirection(int direction) {
    currentDirection = direction;
}

int main() {
    if (gpioInitialise() < 0) {
        std::cerr << "Failed to initialize pigpio!" << std::endl;
        return 1;
    }

    gpioSetMode(stepPin, PI_OUTPUT);
    gpioSetMode(dirPin, PI_OUTPUT);

    // Start a thread to control the motor
    std::thread motorThread(stepMotor, 500);

    // Test code, you can change this part as needed
    setDirection(DIR_FORWARD); // Start rotating clockwise
    sleep(10); // Rotate for 10 seconds
    setDirection(DIR_BACKWARD); // Change to counterclockwise rotation
    sleep(10); // Rotate for 10 seconds
    setDirection(DIR_STOP); // Stop rotating

    motorThread.join(); // Wait for the thread to end

    gpioTerminate();

    return 0;
}
