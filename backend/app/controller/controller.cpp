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

// 初始化定义传送带的GPIO引脚号
Controller::Controller(): 
    motor(19, 17),  // 替换为实际的引脚号(stepPinRight, dirPinRight)
    w1(22, 27),
    w2(6, 5),
    w3(21, 20),
    w4(16, 12),
    w5(25, 24),
    lastWeights(5, 0),
    currentWeights(5, 0) {
        // wiringPiSetup();
}

void Controller::setCallback(std::function<void(bool, const std::vector<int>&)> callback) {
    this->callback = callback;
}

void Controller::readWeight() {
    // 为每个 WeightSensor 实例设置回调
    w1.setCallback([this](int weight) { this->onWeightChange(1, weight); });
    w2.setCallback([this](int weight) { this->onWeightChange(2, weight); });
    w3.setCallback([this](int weight) { this->onWeightChange(3, weight); });
    w4.setCallback([this](int weight) { this->onWeightChange(4, weight); });
    w5.setCallback([this](int weight) { this->onWeightChange(5, weight); });
        
    // 直接使用成员变量读取重量
    w1.weightReading();
    w2.weightReading();
    w3.weightReading();
    w4.weightReading();
    w5.weightReading();

    // double w1_weight = w1.weightReading();
    // double w2_weight = w2.weightReading();
    // double w3_weight = w3.weightReading();
    // double w4_weight = w4.weightReading();
    // double w5_weight = w5.weightReading();

    // std::cerr << "w1_weight" << w1_weight << std::endl;
    // std::cerr << "w2_weight" << w2_weight << std::endl;
    // std::cerr << "w3_weight" << w3_weight << std::endl;
    // std::cerr << "w4_weight" << w4_weight << std::endl;
    // std::cerr << "w5_weight" << w5_weight << std::endl;
}

void Controller::onWeightChange(int sensorId, int weight) {
    // 处理重量变化
    // 这里可以根据 sensorId 和 weight 来执行特定逻辑
    std::cout << "Sensor " << sensorId << " weight changed to " << weight << std::endl;

    if (currentWeights.size() < 5) {
        currentWeights.resize(5, 0.0); // 假设有5个传感器
    }
    // 根据 sensorId 更新对应传感器的重量
    // 注意：这里假设 sensorId 从1开始计数
    currentWeights[sensorId - 1] = weight;
    
    // 检查当前读数是否与上一次读数相同
    bool isSameAsLast = currentWeights.size() == lastWeights.size() && 
                    std::equal(currentWeights.begin(), currentWeights.end(), lastWeights.begin());

    if (!isSameAsLast) {
        // 如果当前读数与上一次不同，则执行回调，传递true和当前重量
        if (callback) {
            callback(true, currentWeights);
        }
        // 更新上一次的重量读数为当前读数
        lastWeights = currentWeights;
    } else {
        // 如果当前读数与上一次相同，则执行回调，传递false和当前重量
        if (callback) {
            callback(false, currentWeights);
        }
    }
}

void Controller::setpControl(const std::string& status, int sensorIndex) {
    // 可以在这里添加基于sensorIndex的逻辑
    std::cout << "Sensor " << sensorIndex << " triggered action: " << status << std::endl;

    if(status == "right"){
        motor.startMoving(StepperMotor::DIR_FORWARD);
    } else if (status == "pause") {
        motor.stop();
    } else if (status == "left") {
        motor.startMoving(StepperMotor::DIR_BACKWARD);
    }
}

// Real-Time Processing 实时处理逻辑
void Controller::RTP(const std::vector<int>& currentWeight) {
    // 假设currentWeight的大小总是5
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
            // std::cout << "Action: left" << angleAcc << std::endl;
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


    // // 对每个传感器的读数独立判断
    // if (currentWeight[0] > 0) {
    //     setpControl("right", 0);  // 第1个传感器特定的操作
    // }
    // if (currentWeight[1] > 0) {
    //     setpControl("right", 1);  // 第2个传感器特定的操作
    // }
    // if (currentWeight[2] > 0) {
    //     setpControl("pause", 2);  // 第3个传感器特定的操作
    // }
    // if (currentWeight[3] > 0) {
    //     setpControl("left", 3);  // 第4个传感器特定的操作
    // }
    // if (currentWeight[4] > 0) {
    //     setpControl("left", 4);  // 第5个传感器特定的操作
    // }
}

void Controller::TurnOff() {
    motor.stop();
}