/**
 * @file   motor_driver_test.cpp
 * @brief  Unit test of step motor
 *
 * @author Yu Qiao
 * @date   2024-03-16
 *
 * Additional notes:
 * - ...
 */

// #define BOOST_TEST_MODULE MotorDriverTest
#include <boost/test/unit_test.hpp>
#include "../app/motor_driver/motor_driver.hpp"
#include "../socket/gpio_lock.hpp"
std::mutex gpioMutex; // Global definition

BOOST_AUTO_TEST_CASE(testMotorStartAndStop) {
    int stepPin = 19; // Hypothetical STEP pin
    int dirPin = 17;  // Assumed DIR pin

    StepperMotor motor(stepPin, dirPin);

    // Test motor starts moving
    motor.startMoving(StepperMotor::DIR_FORWARD);
    BOOST_CHECK(motor.getCurrentDirection() == StepperMotor::DIR_FORWARD);

    motor.startMoving(StepperMotor::DIR_BACKWARD);
    BOOST_CHECK(motor.getCurrentDirection() == StepperMotor::DIR_BACKWARD);

    // Test motor stop
    motor.stop();
    BOOST_CHECK(motor.getCurrentDirection() == StepperMotor::DIR_STOP);
}
