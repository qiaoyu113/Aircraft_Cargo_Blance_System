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
#include "../weight_sensor/hx711_sensor/hx711_sensor.hpp"
#include "../../socket/send_message.hpp"
#include "../motor_driver/motor_driver.hpp"

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
    std::function<void(bool, const std::vector<int>&)> callback; // Update the definition of the callback
    MessageSender messageSender; 
    WeightSensor w1, w2, w3, w4, w5;
    std::vector<int> lastWeights;
    std::vector<int> currentWeights; 
    StepperMotor motor;  // Stepper motor for moving to the leftStepper motor for moving to the left
};

#endif // CONTROLLER_HPP