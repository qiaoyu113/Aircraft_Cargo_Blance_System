#ifndef LEFT_HPP
#define LEFT_HPP

class Left {
public:
    Left(int pin); // Constructor now takes a pin number
    void turnOn();
    void turnOff();
private:
    int pin;
};

#endif // LEFT_HPP