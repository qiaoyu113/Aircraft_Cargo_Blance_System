#ifndef GPIO_LOCK_HPP
#define GPIO_LOCK_HPP

#include <mutex>

// A global mutex that controls access to GPIO resources
extern std::mutex gpioMutex;

#endif // GPIO_LOCK_HPP
