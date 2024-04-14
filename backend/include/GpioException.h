#ifndef HX711_GPIOEXCEPTION_H_895614C3_EF94_4A60_92EC_BA629230B29A
#define HX711_GPIOEXCEPTION_H_895614C3_EF94_4A60_92EC_BA629230B29A

#include <stdexcept>

namespace HX711 {
class GpioException : public std::runtime_error {
public:
    explicit GpioException(const char* what_arg)
        : std::runtime_error(what_arg) { }
};
};
#endif
