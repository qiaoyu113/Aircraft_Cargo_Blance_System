#ifndef LED_HPP
#define LED_HPP

class Led {
public:
    Led();
    void turnOn();
    void turnOff();
private:
    int pin;
};

#endif // LED_HPP