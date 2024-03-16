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

#ifndef WEIGHTSENSOR_HPP
#define WEIGHTSENSOR_HPP

#include <pigpio.h>
#include <functional>

struct hx711_pin {
    int SCK;
    int SDA;
    int EN;                      // 校准使能
    int calibration;             // 校准
    int coefficient;             // 比例系数
    unsigned long value;         // 记录数值
    int weight;                  // 重量
};

class WeightSensor {
public:
    WeightSensor(int pinSCK, int pinSDA);
    void setCallback(std::function<void(int)> callback); // 修改回调函数的参数类型为int
    void weightReading();
    int read_sensor_test();
    
private:
    hx711_pin hx711;
    std::function<void(int)> callback; // 如果您计划使用回调
    void initPin();
    int readSensor(); // 确保返回类型与方法实现匹配
    void setPin(); // 匹配声明与定义
};

#endif // WEIGHTSENSOR_HPP
