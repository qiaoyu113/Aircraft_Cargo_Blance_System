#ifndef PAUSE_HPP
#define PAUSE_HPP

class Pause {
public:
    Pause(int pin);
    void turnOn();
    void turnOff();
private:
    int pin;
};

#endif // PAUSE_HPP