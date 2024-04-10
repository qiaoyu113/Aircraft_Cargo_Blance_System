#include <functional>
#include "../../../include/common.h" // 确保引入了 AdvancedHX711 类的定义

class WeightSensor {
public:
    WeightSensor(int pinSCK, int pinSDA);
    void setCallback(std::function<void(float)> callback);
    void weightReading();
    float read_sensor_test();

private:
    HX711::AdvancedHX711 hx; // 使用 AdvancedHX711 类
    // HX711::SimpleHX711 hx; // 使用 AdvancedHX711 类
    std::function<void(float)> callback;
    void initSensor();
    float readWeight();
    float offset = 0; // 存储偏移量
};
