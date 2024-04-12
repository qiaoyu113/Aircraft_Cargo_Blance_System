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
    void readWeight();            // Correct return type
    void setpControl(const std::string& status, int sensorIndex); // Added parameter and corrected name
    void onWeightChange(int sensorId, int weight); // Add onWeightChange as a member function
    void TurnOff();
    void RTP(const std::vector<int>& currentWeight);
private:
    int pin;
    Right right;
    Pause pause;
    Left left;
    std::function<void(bool, const std::vector<int>&)> callback; // Update the definition of the callback
    MessageSender messageSender; 
    
    WeightSensor w1, w2, w3, w4, w5;
    std::vector<int> lastWeights;
    std::vector<int> currentWeights; 
};

#endif // CONTROLLER_HPP