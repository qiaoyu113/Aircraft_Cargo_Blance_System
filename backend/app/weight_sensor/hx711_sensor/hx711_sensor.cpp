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

/usr/bin/ld: CMakeFiles/all_tests.dir/app/weight_sensor/hx711_sensor/hx711_sensor.cpp.o: in function `WeightSensor::WeightSensor(int, int)':
hx711_sensor.cpp:(.text+0x0): multiple definition of `WeightSensor::WeightSensor(int, int)'; CMakeFiles/all_tests.dir/tests/weight_sensor_test.cpp.o:weight_sensor_test.cpp:(.text+0x1f574): first defined here
/usr/bin/ld: CMakeFiles/all_tests.dir/app/weight_sensor/hx711_sensor/hx711_sensor.cpp.o: in function `WeightSensor::initSensor()':
hx711_sensor.cpp:(.text+0x114): multiple definition of `WeightSensor::initSensor()'; CMakeFiles/all_tests.dir/tests/weight_sensor_test.cpp.o:weight_sensor_test.cpp:(.text+0x1f688): first defined here
/usr/bin/ld: CMakeFiles/all_tests.dir/app/weight_sensor/hx711_sensor/hx711_sensor.cpp.o: in function `WeightSensor::WeightSensor(int, int)':
hx711_sensor.cpp:(.text+0x0): multiple definition of `WeightSensor::WeightSensor(int, int)'; CMakeFiles/all_tests.dir/tests/weight_sensor_test.cpp.o:weight_sensor_test.cpp:(.text+0x1f574): first defined here
/usr/bin/ld: CMakeFiles/all_tests.dir/app/weight_sensor/hx711_sensor/hx711_sensor.cpp.o: in function `WeightSensor::readWeight()':
hx711_sensor.cpp:(.text+0x14c): multiple definition of `WeightSensor::readWeight()'; CMakeFiles/all_tests.dir/tests/weight_sensor_test.cpp.o:weight_sensor_test.cpp:(.text+0x1f6c0): first defined here
/usr/bin/ld: CMakeFiles/all_tests.dir/app/weight_sensor/hx711_sensor/hx711_sensor.cpp.o: in function `WeightSensor::weightReading()':
hx711_sensor.cpp:(.text+0x2d8): multiple definition of `WeightSensor::weightReading()'; CMakeFiles/all_tests.dir/tests/weight_sensor_test.cpp.o:weight_sensor_test.cpp:(.text+0x1f84c): first defined here
/usr/bin/ld: CMakeFiles/all_tests.dir/app/weight_sensor/hx711_sensor/hx711_sensor.cpp.o: in function `WeightSensor::setCallback(std::function<void (float)>)':
hx711_sensor.cpp:(.text+0x338): multiple definition of `WeightSensor::setCallback(std::function<void (float)>)'; CMakeFiles/all_tests.dir/tests/weight_sensor_test.cpp.o:weight_sensor_test.cpp:(.text+0x1f8ac): first defined here
/usr/bin/ld: CMakeFiles/all_tests.dir/app/weight_sensor/hx711_sensor/hx711_sensor.cpp.o: in function `WeightSensor::read_sensor_test()':
hx711_sensor.cpp:(.text+0x36c): multiple definition of `WeightSensor::read_sensor_test()'; CMakeFiles/all_tests.dir/tests/weight_sensor_test.cpp.o:weight_sensor_test.cpp:(.text+0x1f8e0): first defined here
/usr/bin/ld: CMakeFiles/all_tests.dir/tests/weight_sensor_test.cpp.o: in function `WeightSensor::WeightSensor(int, int)':
weight_sensor_test.cpp:(.text+0x1f59c): undefined reference to `HX711::Value::Value(int)'
/usr/bin/ld: weight_sensor_test.cpp:(.text+0x1f5ac): undefined reference to `HX711::Value::Value(int)'
/usr/bin/ld: weight_sensor_test.cpp:(.text+0x1f5d0): undefined reference to `HX711::AdvancedHX711::AdvancedHX711(int, int, HX711::Value, HX711::Value, HX711::Rate)'
/usr/bin/ld: weight_sensor_test.cpp:(.text+0x1f668): undefined reference to `HX711::AdvancedHX711::~AdvancedHX711()'
/usr/bin/ld: CMakeFiles/all_tests.dir/tests/weight_sensor_test.cpp.o: in function `WeightSensor::readWeight()':
weight_sensor_test.cpp:(.text+0x1f710): undefined reference to `HX711::AbstractScale::weight(std::chrono::duration<long long, std::ratio<1ll, 1000000000ll> >)'
/usr/bin/ld: weight_sensor_test.cpp:(.text+0x1f71c): undefined reference to `HX711::Mass::getValue() const'
/usr/bin/ld: CMakeFiles/all_tests.dir/tests/weight_sensor_test.cpp.o: in function `WeightSensor::~WeightSensor()':
weight_sensor_test.cpp:(.text._ZN12WeightSensorD2Ev[_ZN12WeightSensorD5Ev]+0x28): undefined reference to `HX711::AdvancedHX711::~AdvancedHX711()'
/usr/bin/ld: CMakeFiles/all_tests.dir/app/weight_sensor/hx711_sensor/hx711_sensor.cpp.o: in function `WeightSensor::WeightSensor(int, int)':
hx711_sensor.cpp:(.text+0x28): undefined reference to `HX711::Value::Value(int)'
/usr/bin/ld: hx711_sensor.cpp:(.text+0x38): undefined reference to `HX711::Value::Value(int)'
/usr/bin/ld: hx711_sensor.cpp:(.text+0x5c): undefined reference to `HX711::AdvancedHX711::AdvancedHX711(int, int, HX711::Value, HX711::Value, HX711::Rate)'
/usr/bin/ld: hx711_sensor.cpp:(.text+0xf4): undefined reference to `HX711::AdvancedHX711::~AdvancedHX711()'
/usr/bin/ld: CMakeFiles/all_tests.dir/app/weight_sensor/hx711_sensor/hx711_sensor.cpp.o: in function `WeightSensor::readWeight()':
hx711_sensor.cpp:(.text+0x19c): undefined reference to `HX711::AbstractScale::weight(std::chrono::duration<long long, std::ratio<1ll, 1000000000ll> >)'
/usr/bin/ld: hx711_sensor.cpp:(.text+0x1a8): undefined reference to `HX711::Mass::getValue() const'
collect2: error: ld returned 1 exit status
make[2]: *** [CMakeFiles/all_tests.dir/build.make:150: all_tests] Error 1
make[1]: *** [CMakeFiles/Makefile2:97: CMakeFiles/all_tests.dir/all] Error 2
make: *** [Makefile:114: all] Error 2