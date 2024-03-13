// #include <iostream>
// #include <pigpio.h>
// #include <unistd.h>

// // 定义STEP和DIR引脚
// const int stepPin = 19; // 使用BCM引脚编号，根据实际连接修改
// const int dirPin = 17;  // 使用BCM引脚编号，根据实际连接修改

// // 定义方向常量
// const int DIR_FORWARD = PI_HIGH; // 或者任何代表正向的值
// const int DIR_BACKWARD = PI_LOW; // 或者任何代表反向的值

// void stepMotor(int steps, int delayUs, int direction) {
//     gpioWrite(dirPin, direction); // 设置电机方向
//     for (int i = 0; i < steps; i++) {
//         gpioWrite(stepPin, 1);
//         usleep(delayUs);
//         gpioWrite(stepPin, 0);
//         usleep(delayUs);
//         //printf("doing so");
//     }
// }

// int main() {
//     if (gpioInitialise() < 0) {
//         std::cerr << "pigpio初始化失败！" << std::endl;
//         return 1;
//     }

//     // 设置GPIO引脚模式
//     gpioSetMode(stepPin, PI_OUTPUT);
//     gpioSetMode(dirPin, PI_OUTPUT);

//     // 旋转步进电机
//     stepMotor(800, 500, DIR_FORWARD); // 正向旋转200步
//     stepMotor(800, 500, DIR_BACKWARD); // 反向旋转200步

//     gpioTerminate();

//     return 0;
// }


#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include <thread>

// 定义STEP和DIR引脚
const int stepPin = 19;
const int dirPin = 17;

// 定义方向常量
const int DIR_FORWARD = PI_HIGH;
const int DIR_BACKWARD = PI_LOW;
const int DIR_STOP = -1; // 增加一个代表停止的状态

// 当前方向的全局变量
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
        std::cerr << "pigpio初始化失败！" << std::endl;
        return 1;
    }

    gpioSetMode(stepPin, PI_OUTPUT);
    gpioSetMode(dirPin, PI_OUTPUT);

    // 启动一个线程来控制电机
    std::thread motorThread(stepMotor, 500);

    // 测试代码，你可以根据需要改变这部分
    setDirection(DIR_FORWARD); // 开始顺时针旋转
    sleep(10); // 旋转10秒
    setDirection(DIR_BACKWARD); // 改为逆时针旋转
    sleep(10); // 旋转10秒
    setDirection(DIR_STOP); // 停止旋转

    motorThread.join(); // 等待线程结束

    gpioTerminate();

    return 0;
}