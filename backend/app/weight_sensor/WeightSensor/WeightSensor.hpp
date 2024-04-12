// #ifndef WEIGHTSENSOR_HPP
// #define WEIGHTSENSOR_HPP

// #include <functional>

// class WeightSensor {
// public:
//     WeightSensor(int pin); // 构造函数声明
//     void setCallback(std::function<void(bool)> callback); // 设置回调函数
//     bool weightReading(); // 读取重量

// private:
//     int pin; // GPIO引脚号
//     std::function<void(bool)> callback; // 回调函数
// };

// #endif // WEIGHTSENSOR_HPP


/**
 * @file   WeightSensor.hpp
 * @brief  Gravity sensor code file
 *
 * @author Yuhan Liu
 * @date   2024-02-20
 *
 * Additional notes:
 * - ...
 */

#ifndef WEIGHTSENSOR_HPP
#define WEIGHTSENSOR_HPP

#include <pigpio.h>
#include <functional>

struct hx711_pin {
    int SCK;
    int SDA;
    int EN;                      // Calibration enable
    int calibration;             // Calibration
    int coefficient;             // Scale factor
    unsigned long value;         // Record value
    int weight;                  // Weight          
};

class WeightSensor {
public:
    WeightSensor(int pinSCK, int pinSDA);
    void setCallback(std::function<void(int)> callback); // Modify the parameter type of the callback function to int
    void weightReading();
    int read_sensor_test();
    
private:
    hx711_pin hx711;
    std::function<void(int)> callback; // If you plan to use a callback
    void initPin();
    int readSensor(); // Ensure the return type matches the method implementation
    void setPin(); // Match declaration with definition
};

#endif // WEIGHTSENSOR_HPP
