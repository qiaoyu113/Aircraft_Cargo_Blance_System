#include <iostream>
#include "controller.hpp"
// #include <wiringPi.h>
#include <pigpio.h>

double accLimit=1;

// 初始化定义传送带的GPIO引脚号
Controller::Controller(): left(29), pause(28), right(27), w1(24), w2(0), w3(2), w4(3), w5(25) {
    // wiringPiSetup();
    // 为每个WeightSensor注册回调函数
    w1.setCallback([this](bool detected) { this->onWeightDetected(1, detected); });
    w2.setCallback([this](bool detected) { this->onWeightDetected(2, detected); });
    w3.setCallback([this](bool detected) { this->onWeightDetected(3, detected); });
    w4.setCallback([this](bool detected) { this->onWeightDetected(4, detected); });
    w5.setCallback([this](bool detected) { this->onWeightDetected(5, detected); });
}

void Controller::onWeightDetected(int sensorIndex, bool detected) {
    std::vector<double> weights = readWeight();
    if (detected) {
        if (callback) {
            callback(true, weights);
        }
    }
}

void Controller::setCallback(std::function<void(bool, const std::vector<double>&)> callback) {
    this->callback = callback;
}

std::vector<double> Controller::readWeight() {
    // 直接使用成员变量读取重量
    double w1_weight = w1.weightReading();
    double w2_weight = w2.weightReading();
    double w3_weight = w3.weightReading();
    double w4_weight = w4.weightReading();
    double w5_weight = w5.weightReading();

    // std::cerr << "w1_weight" << w1_weight << std::endl;
    // std::cerr << "w2_weight" << w2_weight << std::endl;
    // std::cerr << "w3_weight" << w3_weight << std::endl;
    // std::cerr << "w4_weight" << w4_weight << std::endl;
    // std::cerr << "w5_weight" << w5_weight << std::endl;

    std::vector<double> weights = {w1_weight, w2_weight, w3_weight, w4_weight, w5_weight};
    
    // 检查是否所有读数都不为0
    bool allNonZero = std::none_of(weights.begin(), weights.end(), [](double weight) {
        return weight == 0.0;
    });

    // 如果所有读数都不为0，则执行回调
    if (allNonZero) {
        TurnOff();
    }

    return weights;
}

void Controller::setpControl(const std::string& status, int sensorIndex) {
    // 可以在这里添加基于sensorIndex的逻辑
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

// Real-Time Processing 实时处理逻辑
void Controller::RTP(const std::vector<double>& currentWeight) {
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
            std::cout << "Action:lefet " << angleAcc << std::endl;
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
            std::cout << "Action:right " << angleAcc << std::endl;
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
    right.turnOff();
    pause.turnOff();
    left.turnOff();
}