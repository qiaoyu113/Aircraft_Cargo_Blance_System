/**
 * @file   contoller.cpp
 * @brief  Total control center, through which all sensors and stepper motors are empowered
 *
 * @author Yu Qiao
 * @date   2024-02-16
 *
 * Additional notes:
 * - ...
 */

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include <vector>
#include <functional>
// #include "../stepping_motor/left/left.hpp"
// #include "../stepping_motor/right/right.hpp"
// #include "../stepping_motor/pause/pause.hpp"
// #include "../weight_sensor/w1/w1.hpp"
// #include "../weight_sensor/w2/w2.hpp"
// #include "../weight_sensor/w3/w3.hpp"
// #include "../weight_sensor/w4/w4.hpp"
// #include "../weight_sensor/w5/w5.hpp"
#include "../weight_sensor/WeightSensor/WeightSensor.hpp"
#include "../../socket/send_message.hpp"
#include "../motor_driver/motor_driver.hpp"

class Controller {
public:
    Controller();
    void setCallback(std::function<void(bool, const std::vector<int>&)> callback);
    void readWeight();            // Correct return type
    void setpControl(const std::string& status, int sensorIndex); // Added parameter and corrected name
    void onWeightChange(int sensorId, int weight); // 将onWeightChange添加为成员函数
    void TurnOff();
    void RTP(const std::vector<int>& currentWeight);
private:
    int pin;
    // Right right;
    // Pause pause;
    // Left left;
    std::function<void(bool, const std::vector<int>&)> callback; // 更新回调函数的定义
    MessageSender messageSender; 
    // 重量传感器对象作为成员变量
    // W1 w1;
    // W2 w2;
    // W3 w3;
    // W4 w4;
    // W5 w5;
    WeightSensor w1, w2, w3, w4, w5;
    std::vector<int> lastWeights;
    std::vector<int> currentWeights; 
    StepperMotor motor;  // 用于向左移动的步进电机
};

#endif // CONTROLLER_HPP