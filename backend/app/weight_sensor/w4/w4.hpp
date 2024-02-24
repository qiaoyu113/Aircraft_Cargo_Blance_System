#ifndef W4_HPP
#define W4_HPP

#include <functional>

class W4 {
public:
    W4();

    void setCallback(std::function<void(bool)> callback);

    bool weightReading();

private:
    int pin;
    std::function<void(bool)> callback;
};

#endif // W4_HPP
