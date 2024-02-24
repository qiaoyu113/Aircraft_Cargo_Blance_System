#ifndef RIGHT_HPP
#define RIGHT_HPP

class Right {
public:
    Right(int pin);
    void turnOn();
    void turnOff();
private:
    int pin;
};

#endif // RIGHT_HPP