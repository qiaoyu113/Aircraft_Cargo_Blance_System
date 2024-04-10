#include <functional>
#include "../../../include/AdvancedHX711.h" // 确保引入了 AdvancedHX711 类的定义

class WeightSensor {
public:
    WeightSensor(int pinSCK, int pinSDA, int refUnit, int offset);
    void setCallback(std::function<void(float)> callback);
    void weightReading();
    int read_sensor_test();

private:
    HX711::AdvancedHX711 hx; // 使用 AdvancedHX711 类
    std::function<void(float)> callback;
    void initSensor();
    float readWeight();
    float offset = 0; // 存储偏移量
};
