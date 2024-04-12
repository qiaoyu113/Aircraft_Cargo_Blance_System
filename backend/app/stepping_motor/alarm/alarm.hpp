/**
 * @file   alarm.hpp
 * @brief  Header for stepper motor driver functionality
 *
 * Control the motor and issue a warning signal
 *
 * @author Yuhan Liu
 * @date   2024-03-05
 */

#ifndef ALARM_HPP
#define ALARM_HPP

class Alarm {
public:
    Alarm(int pin); // Constructor now takes a pin number
    void turnOn();
    void turnOff();
private:
    int pin;
};

#endif // ALARM_HPP