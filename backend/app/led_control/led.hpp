/**
 * @file   led.cpp
 * @brief  Led executive file
 *
 * @author Yu Qiao
 * @date   2024-02-02
 *
 * Additional notes:
 * - ...
 */

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