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