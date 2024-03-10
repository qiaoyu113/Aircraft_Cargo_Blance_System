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

void WeightSensor::setPin(int pinSCK, int pinSDA) {
    hx711.EN = 1;
    hx711.coefficient = 415; // 根据实际情况调整
}

void WeightSensor::initPin() {
    gpioSetMode(hx711.SCK, PI_OUTPUT);
    gpioSetMode(hx711.SDA, PI_INPUT);
    gpioSetPullUpDown(hx711.SDA, PI_PUD_UP);
}

void WeightSensor::readSensor() {
    // 实现readSensor函数的代码，根据您提供的readSensor函数修改
    // 注意：这里需要调整代码来适配类成员变量的使用
    // ...
    // 调用callback，传递weight值
    int i;
    gpioWrite(hx711->SCK, PI_LOW);
    while(gpioRead(hx711->SCK));
    hx711->value = 0;
    while(gpioRead(hx711->SDA));
    time_sleep(0.1);           // 延时100ms
    for(i=0; i<24; i++){
        gpioWrite(hx711->SCK, PI_HIGH);
        while(gpioRead(hx711->SCK) == 0) gpioDelay(1000);
        hx711->value = hx711->value << 1;
        gpioWrite(hx711->SCK, PI_LOW);
        while(gpioRead(hx711->SCK));
        if(gpioRead(hx711->SDA)){
            hx711->value++;
        }
        gpioWrite(hx711->SCK, PI_LOW);
    }
    gpioWrite(hx711->SCK, PI_HIGH);
    // value->value = value->value ^ 0x800000;
    gpioWrite(hx711->SCK, PI_LOW);

    if((hx711->EN == 1) && (hx711->value < 25000)){
        hx711->EN = 0;
        hx711->calibration = hx711->value;
    } else {
        i = (hx711->value - hx711->calibration + 50) / hx711->coefficient;
    }
    if(i < 5000) hx711->weight = i;
    printf("重量为：%d g\n", hx711->weight);
    return hx711->weight;
}

bool WeightSensor::weightReading() {
    int weight = readSensor();
    return weight; // 根据实际情况返回是否检测到重量的标志
}
