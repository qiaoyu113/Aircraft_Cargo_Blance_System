#ifndef W3_HPP
#define W3_HPP

#include <functional>

class W3 {
public:
    W3(int pin);

    void setCallback(std::function<void(bool)> callback);

    bool weightReading();

private:
    int pin;
    std::function<void(bool)> callback;
};

#endif // W3_HPP
