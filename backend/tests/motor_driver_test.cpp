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

#define BOOST_TEST_MODULE MotorDriverTest
#include <boost/test/unit_test.hpp>
#include "../app/motor_driver/motor_driver.hpp"

BOOST_AUTO_TEST_CASE(testMotorStartAndStop) {
    int stepPin = 19; // 假设的STEP引脚
    int dirPin = 17;  // 假设的DIR引脚

    StepperMotor motor(stepPin, dirPin);

    // 测试电机开始移动
    motor.startMoving(StepperMotor::DIR_FORWARD);
    BOOST_CHECK(motor.getCurrentDirection() == StepperMotor::DIR_FORWARD);

    motor.startMoving(StepperMotor::DIR_BACKWARD);
    BOOST_CHECK(motor.getCurrentDirection() == StepperMotor::DIR_BACKWARD);

    // 测试电机停止
    motor.stop();
    BOOST_CHECK(motor.getCurrentDirection() == StepperMotor::DIR_STOP);
}
