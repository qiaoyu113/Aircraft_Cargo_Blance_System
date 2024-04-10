#include "hx711_sensor.hpp"
#include <pigpio.h>
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>

WeightSensor::WeightSensor(int pinSCK, int pinSDA, int refUnit, int offset) 
    : hx(pinSCK, pinSDA, refUnit, offset) {
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
    // 假设我们使用的是毫秒级延迟来获取权重
    auto weight = hx.weight(std::chrono::milliseconds(250)).toGrams(); // 读取重量，转换为克
    return weight - offset; // 返回调整后的重量
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

int WeightSensor::read_sensor_test() {
    float weight = readWeight();
    return weight;
}