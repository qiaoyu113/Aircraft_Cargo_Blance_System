#ifndef W1_HPP
#define W1_HPP

#include <functional>

class W1 {
public:
    W1(int pin);

    void setCallback(std::function<void(bool)> callback);

    bool weightReading();

private:
    int pin;
    std::function<void(bool)> callback;
};

#endif // W1_HPP
