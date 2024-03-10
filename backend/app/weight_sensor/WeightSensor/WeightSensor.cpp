// #include "WeightSensor.hpp"
// #include <pigpio.h>
// #include <iostream>
// #include <stdexcept>

// // 构造函数实现
// WeightSensor::WeightSensor(int pin) : pin(pin) {
//     if (gpioInitialise() < 0) {
//         throw std::runtime_error("pigpio initialization failed");
//     }
//     gpioSetMode(pin, PI_INPUT);
//     gpioSetPullUpDown(pin, PI_PUD_DOWN);
// }

// // 设置回调函数
// void WeightSensor::setCallback(std::function<void(bool)> callback) {
//     this->callback = callback;
// }

// // 读取重量并触发回调
// bool WeightSensor::weightReading() {
//     bool weightDetected = gpioRead(pin) == PI_HIGH;
//     if (callback) {
//         callback(weightDetected);
//     }
//     return weightDetected;
// }

#include "WeightSensor.hpp"
#include <iostream>
#include <stdexcept>

WeightSensor::WeightSensor(int pinSCK, int pinSDA) {
    hx711.SCK = pinSCK;
    hx711.SDA = pinSDA;
    if (gpioInitialise() < 0) {
        throw std::runtime_error("pigpio initialization failed");
    }
    setPin();
    initPin();
}

void WeightSensor::setCallback(std::function<void(int)> callback) {
    this->callback = callback;
}

void WeightSensor::setPin() {
    hx711.EN = 1;
    hx711.coefficient = 415; // 根据实际情况调整
}

void WeightSensor::initPin() {
    gpioSetMode(hx711.SCK, PI_OUTPUT);
    gpioSetMode(hx711.SDA, PI_INPUT);
    gpioSetPullUpDown(hx711.SDA, PI_PUD_UP);
}

void WeightSensor::start() {
    // 实现start函数的代码，根据您提供的start函数修改
    // 注意：这里需要调整代码来适配类成员变量的使用
    // ...
    // 调用callback，传递weight值
    int i;
    gpioWrite(value->SCK, PI_LOW);
    while(gpioRead(value->SCK));
    value->value = 0;
    while(gpioRead(value->SDA));
    time_sleep(0.1);           // 延时100ms
    for(i=0; i<24; i++){
        gpioWrite(value->SCK, PI_HIGH);
        while(gpioRead(value->SCK) == 0) gpioDelay(1000);
        value->value = value->value << 1;
        gpioWrite(value->SCK, PI_LOW);
        while(gpioRead(value->SCK));
        if(gpioRead(value->SDA)){
            value->value++;
        }
        gpioWrite(value->SCK, PI_LOW);
    }
    gpioWrite(value->SCK, PI_HIGH);
    // value->value = value->value ^ 0x800000;
    gpioWrite(value->SCK, PI_LOW);

    if((value->EN == 1) && (value->value < 25000)){
        value->EN = 0;
        value->calibration = value->value;
    } else {
        i = (value->value - value->calibration + 50) / value->coefficient;
    }
    if(i < 5000) value->weight = i;
    printf("重量为：%d g\n", value->weight);
    if (callback) {
        callback(value->weight);
    }
}

bool WeightSensor::weightReading() {
    start(); // 调用start以读取重量
    return true; // 根据实际情况返回是否检测到重量的标志
}
