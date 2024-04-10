#include "hx711_sensor.hpp"
#include <pigpio.h>
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>

WeightSensor::WeightSensor(int pinSCK, int pinSDA) 
    : hx(pinSCK, pinSDA, 1, 0) {
    if (gpioInitialise() < 0) {
        throw std::runtime_error("pigpio initialization failed");
    }
    initSensor();
}

void WeightSensor::initSensor() {
    // 进行去皮：读取初始重量作为偏移量
    float initialWeight = readWeight(); // 读取初始重量
    this->offset = initialWeight; // 存储初始重量作为偏移量
}

float WeightSensor::readWeight() {
        // 获取重量，返回 Mass 类型
    // auto weightMass = hx.weight(std::chrono::milliseconds(250));
    auto weightMass = hx.weight(std::chrono::seconds(1));

    double m = weightMass.getValue();
    float weightFloat = static_cast<float>(m);

    // 返回调整后的重量
    return weightFloat - offset;
}

void WeightSensor::weightReading() {
    std::thread([this]() {
        float lastWeight = -1;
        while (true) {
            float currentWeight = readWeight();
            std::cout << "Current Weight: " << currentWeight << "g" << std::endl;
            if (currentWeight != lastWeight) {
                if (callback) {
                    callback(currentWeight);
                }
                lastWeight = currentWeight;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1)); // 每秒检查一次
        }
    }).detach();
}

void WeightSensor::setCallback(std::function<void(float)> callback) {
    this->callback = callback;
}

float WeightSensor::read_sensor_test() {
    float weight = readWeight();
    return weight;
}
