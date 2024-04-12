/**
 * @file   button.cpp
 * @brief  Button executive file
 *
 * @author Yuhan Liu
 * @date   2024-02-02
 *
 * Additional notes:
 * - ...
 */

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>

class Button {
public:
    Button();

    void setCallback(std::function<void(bool)> callback);

    bool isPressed();

private:
    int pin;
    std::function<void(bool)> callback;
};

#endif // BUTTON_HPP
