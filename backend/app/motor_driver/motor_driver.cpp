#include <iostream>
#include <pigpio.h>
#include <unistd.h>

// 定义STEP和DIR引脚
const int stepPin = 19; // 使用BCM引脚编号，根据实际连接修改
const int dirPin = 17;  // 使用BCM引脚编号，根据实际连接修改

// 定义方向常量
const int DIR_FORWARD = PI_HIGH; // 或者任何代表正向的值
const int DIR_BACKWARD = PI_LOW; // 或者任何代表反向的值

void stepMotor(int steps, int delayUs, int direction) {
    gpioWrite(dirPin, direction); // 设置电机方向
    for (int i = 0; i < steps; i++) {
        gpioWrite(stepPin, 1);
        usleep(delayUs);
        gpioWrite(stepPin, 0);
        usleep(delayUs);
        //printf("doing so");
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

    // 旋转步进电机
    stepMotor(800, 500, DIR_FORWARD); // 正向旋转200步
    stepMotor(800, 500, DIR_BACKWARD); // 反向旋转200步

    gpioTerminate();

    return 0;
}

