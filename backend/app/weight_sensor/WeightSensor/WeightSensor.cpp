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
#include <thread>

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

int WeightSensor::readSensor() {
    int i;
    gpioWrite(hx711.SCK, PI_LOW);
    while(gpioRead(hx711.SCK));
    hx711.value = 0;
    while(gpioRead(hx711.SDA));
    time_sleep(0.1); // 延时100ms
    for(i = 0; i < 24; i++) {
        gpioWrite(hx711.SCK, PI_HIGH);
        while(!gpioRead(hx711.SCK)) gpioDelay(1000);
        hx711.value <<= 1;
        gpioWrite(hx711.SCK, PI_LOW);
        while(gpioRead(hx711.SCK));
        if(gpioRead(hx711.SDA)) {
            hx711.value++;
        }
    }
    gpioWrite(hx711.SCK, PI_HIGH);
    gpioWrite(hx711.SCK, PI_LOW);

    if((hx711.EN == 1) && (hx711.value < 25000)) {
        hx711.EN = 0;
        hx711.calibration = hx711.value;
    } else {
        i = (hx711.value - hx711.calibration + 50) / hx711.coefficient;
    }
    if(i < 5000) hx711.weight = i;

    return hx711.weight;
}

void WeightSensor::weightReading() {
    std::thread([this]() {
        float lastWeight = -1; // 初始值设为一个不可能的重量，确保第一次总是触发回调
        while (true) {
            float currentWeight = readSensor(); // 读取当前重量，需要根据实际情况实现 readSensor 方法
            if (currentWeight != lastWeight) {
                if (callback) {
                    callback(currentWeight); // 当重量变化时调用回调函数
                }
                lastWeight = currentWeight; // 更新最后的重量记录
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 调整检测频率
        }
    }).detach(); // 分离线程，让它独立运行
    // int weight = readSensor();
    // return weight; // 根据实际情况返回是否检测到重量的标志
}

int WeightSensor::read_sensor_test() {
    int weight = readSensor();
    return weight;
}
