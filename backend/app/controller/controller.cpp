#include <iostream>
#include "controller.hpp"
#include <wiringPi.h>

// 初始化定义传送带的GPIO引脚号
Controller::Controller(): left(29), pause(28), right(27), w1(7), w2(0), w3(2), w4(3), w5(21) {
    // wiringPiSetup();
}

void Controller::setCallback(std::function<void(bool)> callback) {
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

    return {w1_weight, w2_weight, w3_weight, w4_weight, w5_weight};
}

void Controller::setpControl(const std::string& status) {
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

    // 检查是否满足特定条件以调用对应的控制函数
    if (currentWeight[0] > 0 || currentWeight[1] > 0) {
        setpControl("right");
    } else if (currentWeight[2] > 0) {
        setpControl("pause");
    } else if (currentWeight[3] > 0 || currentWeight[4] > 0) {
        setpControl("left");
    }
}

void Controller::TurnOff() {
    right.turnOff();
    pause.turnOff();
    left.turnOff();
}