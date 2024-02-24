#ifndef W2_HPP
#define W2_HPP

#include <functional>

class W2 {
public:
    W2();

    void setCallback(std::function<void(bool)> callback);

    bool weightReading();

private:
    int pin;
    std::function<void(bool)> callback;
};

#endif // W2_HPP
