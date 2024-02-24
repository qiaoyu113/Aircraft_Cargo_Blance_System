#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include <vector>
#include <functional>
#include "../stepping_motor/left/left.hpp"
#include "../stepping_motor/right/right.hpp"
#include "../stepping_motor/pause/pause.hpp"
#include "../weight_sensor/w1/w1.hpp"
#include "../weight_sensor/w2/w2.hpp"
#include "../weight_sensor/w3/w3.hpp"
#include "../weight_sensor/w4/w4.hpp"
#include "../weight_sensor/w5/w5.hpp"

class Controller {
public:
    Controller();
    std::vector<double> readWeight(); // Correct return type
    void setpControl(const std::string& status); // Added parameter and corrected name
    void TurnOff();
    void RTP(const std::vector<double>& currentWeight);
private:
    int pin;
    Right right;
    Pause pause;
    Left left;
    std::function<void(bool)> callback;
    // 重量传感器对象作为成员变量
    W1 w1;
    W2 w2;
    W3 w3;
    W4 w4;
    W5 w5;
};

#endif // CONTROLLER_HPP