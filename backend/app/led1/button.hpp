#ifndef BUTTON_HPP
#define BUTTON_HPP

class Button {
public:
    Button();
    bool isPressed();
private:
    int pin;
};

#endif // BUTTON_HPP