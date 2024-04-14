#ifndef HX711_TIMEOUTEXCEPTION_H_75EF3389_6288_47DC_94F1_444516247301
#define HX711_TIMEOUTEXCEPTION_H_75EF3389_6288_47DC_94F1_444516247301

#include <stdexcept>

namespace HX711 {
class TimeoutException : public std::runtime_error {
public:
    explicit TimeoutException(const char* what_arg)
        : std::runtime_error(what_arg) { }
};
};
#endif
