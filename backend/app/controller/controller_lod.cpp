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

#include <iostream>
#include "controller.hpp"
// #include <wiringPi.h>
#include <pigpio.h>

double accLimit=1;

// Initialize the GPIO pin number that defines the conveyor belt
Controller::Controller(): left(29), pause(28), right(27), w1(24, 27), w2(0, 1), w3(2, 5), w4(3, 4), w5(25,23), lastWeights(5, 0), currentWeights(5, 0) {
    // wiringPiSetup();
}

void Controller::setCallback(std::function<void(bool, const std::vector<int>&)> callback) {
    this->callback = callback;
}

void Controller::readWeight() {
    // Set a callback for each WeightSensor instance
    w1.setCallback([this](int weight) { this->onWeightChange(1, weight); });
    w2.setCallback([this](int weight) { this->onWeightChange(2, weight); });
    w3.setCallback([this](int weight) { this->onWeightChange(3, weight); });
    w4.setCallback([this](int weight) { this->onWeightChange(4, weight); });
    w5.setCallback([this](int weight) { this->onWeightChange(5, weight); });
        
    // Read weights directly using member variables
    w1.weightReading();
    w2.weightReading();
    w3.weightReading();
    w4.weightReading();
    w5.weightReading();

}

void Controller::onWeightChange(int sensorId, int weight) {
    // Handling weight changes
    // Specific logic can be performed based on sensorId and weight
    std::cout << "Sensor " << sensorId << " weight changed to " << weight << std::endl;

    if (currentWeights.size() < 5) {
        currentWeights.resize(5, 0.0); // Suppose there are five sensors
    }
    // Update the weight of the corresponding sensor according to sensorId
    // Note: Here it is assumed that sensorId starts counting from 1
    currentWeights[sensorId - 1] = weight;
    
    // Check if the current reading is the same as the last reading
    bool isSameAsLast = currentWeights.size() == lastWeights.size() && 
                    std::equal(currentWeights.begin(), currentWeights.end(), lastWeights.begin());

    if (!isSameAsLast) {
        // If the current reading is different from the last, the callback is executed, passing true and the current weight
        if (callback) {
            callback(true, currentWeights);
        }
        // Update the last weight reading to the current reading
        lastWeights = currentWeights;
    } else {
        // If the current reading is the same as the last, the callback is executed, passing false and the current weight
        if (callback) {
            callback(false, currentWeights);
        }
    }
}

void Controller::setpControl(const std::string& status, int sensorIndex) {
    // Sensorindex-based logic can be added here
    std::cout << "Sensor " << sensorIndex << " triggered action: " << status << std::endl;

    if(status == "right"){
        right.turnOn();
        pause.turnOff();
        left.turnOff();
    } else if (status == "pause") {
        right.turnOff();
        pause.turnOn();
        left.turnOff();
    } else if (status == "left") {
        right.turnOff();
        pause.turnOff();
        left.turnOn();
    }
}

// Real-Time Processing logic
void Controller::RTP(const std::vector<int>& currentWeight) {
    // Assume that the size of currentWeight is always 5
    if (currentWeight.size() != 5) {
        std::cerr << "Error: Expected 5 weight readings." << std::endl;
        return;
    }
    
    double weightAll=currentWeight[0]+currentWeight[1]+currentWeight[2]+currentWeight[3]+currentWeight[4];
    double d=2;
    double weightSystem=0;
    double rotationInertia=((weightAll+weightSystem)*4*4*d*d)/12;
    double torqueLeft=9.8*currentWeight[0]*2*d+9.8*currentWeight[1]*d;
    double torqueRight=9.8*currentWeight[4]*2*d+9.8*currentWeight[3]*d;

    if ((currentWeight[0]+currentWeight[1])>(currentWeight[3]+currentWeight[4])) {
        if (weightAll==0){
            setpControl("pause", 0);
        } 
        else{
            double angleAcc=(torqueLeft-torqueRight)/rotationInertia;
            // std::cout << "Action:lefet " << angleAcc << std::endl;
            if (angleAcc<=accLimit){
                setpControl("pause", 0);
            }
            else{
                if (currentWeight[4]!=0){
                    setpControl("alarm",0);
                    setpControl("pause",0);
                }
                else{
                    setpControl("right",0);
                }
            }
        }
    }

    if ((currentWeight[0]+currentWeight[1])<(currentWeight[3]+currentWeight[4])) {
        if (weightAll==0){
            setpControl("pause", 0);
        } 
        else{
            double angleAcc=(torqueRight-torqueLeft)/rotationInertia;
            // std::cout << "Action:right " << angleAcc << std::endl;
            if (angleAcc<=accLimit){
                setpControl("pause", 0);
            }
            else{
                if (currentWeight[0]!=0){
                    setpControl("alarm",0);
                    setpControl("pause",0);
                }
                else{
                    setpControl("left",0);
                }
            }
        }
    }

    if ((currentWeight[0]+currentWeight[1])==(currentWeight[3]+currentWeight[4])){
      setpControl("pause",0);
    }

    
}

void Controller::TurnOff() {
    right.turnOff();
    pause.turnOff();
    left.turnOff();
}