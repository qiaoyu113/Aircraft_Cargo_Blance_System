#ifndef GPIO_LOCK_HPP
#define GPIO_LOCK_HPP

#include <mutex>

// 全局互斥锁，用于控制对GPIO资源的访问
extern std::mutex gpioMutex;

#endif // GPIO_LOCK_HPP
