#ifndef WEIGHTSENSOR_HPP
#define WEIGHTSENSOR_HPP

#include <functional>

class WeightSensor {
public:
    WeightSensor(int pin); // 构造函数声明
    void setCallback(std::function<void(bool)> callback); // 设置回调函数
    bool weightReading(); // 读取重量

private:
    int pin; // GPIO引脚号
    std::function<void(bool)> callback; // 回调函数
};

#endif // WEIGHTSENSOR_HPP
