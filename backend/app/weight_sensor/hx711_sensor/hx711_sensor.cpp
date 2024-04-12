/**
 * @file   hx711_sensor.cpp
 * @brief  Gravity sensor code file
 *
 * @author Yu Qiao
 * @date   2024-04-1
 *
 * Additional notes:
 * - ...
 */

#include "hx711_sensor.hpp"
#include <pigpio.h>
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>

using namespace std;
using std::chrono::milliseconds;
using namespace HX711;

WeightSensor::WeightSensor(int pinSCK, int pinSDA) 
    : hx(pinSDA, pinSCK, -370, -367471, Rate::HZ_80) {
    // : hx(pinSDA, pinSCK, -370, -367471) {
    if (gpioInitialise() < 0) {
        throw std::runtime_error("pigpio initialization failed");
    }
    // hx.setUnit(Mass::Unit::G);
    initSensor();
}

void WeightSensor::initSensor() {
    // 进行去皮：读取初始重量作为偏移量, Peeling: Read the initial weight as an offset
    float initialWeight = readWeight(); // 读取初始重量 Read initial weight
    if (this->offset == 0) {
        this->offset = initialWeight; // 存储初始重量作为偏移量 Stores the initial weight as an offset
    }
}

float WeightSensor::readWeight() {
    std::lock_guard<std::mutex> lock(gpioMutex);
    const Mass weightMass = hx.weight(milliseconds(400));
    string m = weightMass.toString(Mass::Unit::G);

    // 将字符串转换为浮点数
    float weightFloat;
    try {
        weightFloat = -stof(m);
    } catch (const invalid_argument& e) {
        cerr << "Invalid argument: " << e.what() << endl;
        // Handle cases where the conversion fails, such as returning 0 or other default values
        return 0.0f;
    } catch (const out_of_range& e) {
        cerr << "Out of range: " << e.what() << endl;
        // Handle conversion failures
        return 0.0f;
    }

    float val = weightFloat - offset;

    if (val < 100) {
        val = 0;
    }

    // Return the adjusted weight
    return val;
}

void WeightSensor::weightReading() {
    std::thread([this]() {
        float lastWeight = -1;
        while (true) {
            float currentWeight = readWeight();
            std::cout << "--------readWeight" << currentWeight << std::endl;
            // if (currentWeight != lastWeight) {
                if (callback) {
                    callback(currentWeight);
                }
                lastWeight = currentWeight;
            // }
            // std::this_thread::sleep_for(std::chrono::seconds(1)); // 每秒检查一次
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
