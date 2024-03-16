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

// 定义STEP和DIR引脚
const int stepPin = 17; // 使用BCM引脚编号，根据实际连接修改
const int dirPin = 27;  // 使用BCM引脚编号，根据实际连接修改

void stepMotor(int steps, int delayUs) {
    for (int i = 0; i < steps; i++) {
        gpioWrite(stepPin, 1);
        usleep(delayUs);
        gpioWrite(stepPin, 0);
        usleep(delayUs);
    }
}

int main() {
    if (gpioInitialise() < 0) {
        std::cerr << "pigpio初始化失败！" << std::endl;
        return 1;
    }

    // 设置GPIO引脚模式
    gpioSetMode(stepPin, PI_OUTPUT);
    gpioSetMode(dirPin, PI_OUTPUT);

    // 设置电机方向
    gpioWrite(dirPin, PI_HIGH); // 设置为PI_HIGH或PI_LOW以改变方向

    // 旋转步进电机
    stepMotor(200, 1000); // 旋转200步，每步间隔1000微秒

    gpioTerminate();

    return 0;
}