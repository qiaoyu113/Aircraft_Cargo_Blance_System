/**
 * @file   WeightSensor.cpp
 * @brief  Gravity sensor code file
 *
 * @author Yuhan Liu
 * @date   2024-02-20
 *
 * Additional notes:
 * - ...
 */

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
    hx711.coefficient = 415;
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
    time_sleep(0.1);
    for(i = 0; i < 24; i++) {
        gpioWrite(hx711.SCK, PI_HIGH);
        while(gpioRead(hx711.SCK) == 0) gpioDelay(1000);
        hx711.value = hx711.value << 1;
        gpioWrite(hx711.SCK, PI_LOW);
        while(gpioRead(hx711.SCK));
        if(gpioRead(hx711.SDA)) {
            hx711.value++;
        }
        gpioWrite(hx711.SCK, PI_LOW);
    }
    gpioWrite(hx711.SCK, PI_HIGH);

    if((hx711.EN == 1) && (hx711.value > 2500)) {
        hx711.EN = 0;
        hx711.calibration = hx711.value;
    } else {
        i = (hx711.value - hx711.calibration + 50) / hx711.coefficient;
    }
    if(i < 5000) {
      hx711.weight = i;
    }
    return hx711.weight;
}

void WeightSensor::weightReading() {
    std::thread([this]() {
        float lastWeight = -1; // The initial value is set to an impossible weight, ensuring that the callback is always triggered the first time
        while (true) {
            float currentWeight = readSensor(); // To read the current weight, you need to implement the readSensor method according to the actual situation
            std::cout << "------currentWeight------还在循环: " << currentWeight << std::endl;
            if (currentWeight != lastWeight) {
                if (callback) {
                    callback(currentWeight); // Call the callback function when the weight changes
                }
                lastWeight = currentWeight; // Update the last weight record
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1500)); // Adjust detection frequency
        }
    }).detach(); // Separate the thread and let it run independently
    // int weight = readSensor();
    // return weight; // 根据实际情况返回是否检测到重量的标志
}

int WeightSensor::read_sensor_test() {
    int weight = readSensor();
    return weight;
}
