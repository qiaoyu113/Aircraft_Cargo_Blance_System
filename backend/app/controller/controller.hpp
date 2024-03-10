#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include <vector>
#include <functional>
#include "../stepping_motor/left/left.hpp"
#include "../stepping_motor/right/right.hpp"
#include "../stepping_motor/pause/pause.hpp"
// #include "../weight_sensor/w1/w1.hpp"
// #include "../weight_sensor/w2/w2.hpp"
// #include "../weight_sensor/w3/w3.hpp"
// #include "../weight_sensor/w4/w4.hpp"
// #include "../weight_sensor/w5/w5.hpp"
#include "../weight_sensor/WeightSensor/WeightSensor.hpp"
#include "../../socket/send_message.hpp"

class Controller {
public:
    Controller();
    void setCallback(std::function<void(bool, const std::vector<int>&)> callback);
    std::vector<int> readWeight();            // Correct return type
    void setpControl(const std::string& status, int sensorIndex); // Added parameter and corrected name
    void TurnOff();
    void RTP(const std::vector<int>& currentWeight);
private:
    int pin;
    Right right;
    Pause pause;
    Left left;
    std::function<void(bool, const std::vector<int>&)> callback; // 更新回调函数的定义
    void onWeightChange(int sensorId, int weight);
    MessageSender messageSender; 
    // 重量传感器对象作为成员变量
    // W1 w1;
    // W2 w2;
    // W3 w3;
    // W4 w4;
    // W5 w5;
    WeightSensor w1, w2, w3, w4, w5;
    std::vector<int> lastWeights; // 用来存储上一次的重量读数
    std::vector<int> currentWeights; // 当前的重量，初始化为足够大以存储所有传感器的重量
};

#endif // CONTROLLER_HPP