#ifndef W5_HPP
#define W5_HPP

#include <functional>

class W5 {
public:
    W5();

    void setCallback(std::function<void(bool)> callback);

    bool weightReading();

private:
    int pin;
    std::function<void(bool)> callback;
};

#endif // W5_HPP
