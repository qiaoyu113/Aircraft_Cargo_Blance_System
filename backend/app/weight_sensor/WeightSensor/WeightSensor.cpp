#include "WeightSensor.hpp"
#include <pigpio.h>
#include <iostream>
#include <stdexcept>

// 构造函数实现
WeightSensor::WeightSensor(int pin) : pin(pin) {
    if (gpioInitialise() < 0) {
        throw std::runtime_error("pigpio initialization failed");
    }
    gpioSetMode(pin, PI_INPUT);
    gpioSetPullUpDown(pin, PI_PUD_DOWN);
}

// 设置回调函数
void WeightSensor::setCallback(std::function<void(bool)> callback) {
    this->callback = callback;
}

// 读取重量并触发回调
bool WeightSensor::weightReading() {
    bool weightDetected = gpioRead(pin) == PI_HIGH;
    if (callback) {
        callback(weightDetected);
    }
    return weightDetected;
}
