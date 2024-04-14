#ifndef HX711_INTEGRITYEXCEPTION_H_1C3B9E19_80A6_40EF_BD7D_9E6600006E64
#define HX711_INTEGRITYEXCEPTION_H_1C3B9E19_80A6_40EF_BD7D_9E6600006E64

#include <stdexcept>

namespace HX711 {
class IntegrityException : public std::runtime_error {
public:
    explicit IntegrityException(const char* what_arg)
        : std::runtime_error(what_arg) { }
};
};
#endif
