/**
 * @file   hx711_sensor.hpp
 * @brief  Gravity sensor code file
 *
 * @author Yu Qiao
 * @date   2024-04-1
 *
 * Additional notes:
 * - ...
 */

#include <functional>
#include "../../../include/common.h"
#include "../../../socket/gpio_lock.hpp"

class WeightSensor {
public:
    WeightSensor(int pinSCK, int pinSDA);
    void setCallback(std::function<void(float)> callback);
    void weightReading();
    float read_sensor_test();

private:
    HX711::AdvancedHX711 hx; 
    // HX711::SimpleHX711 hx; 
    std::function<void(float)> callback;
    void initSensor();
    float readWeight();
    float offset = 0;
};
