#ifndef HX711_VALUESTACK_H_609AB3D7_0D6C_45EE_8864_5A1D5E866ACA
#define HX711_VALUESTACK_H_609AB3D7_0D6C_45EE_8864_5A1D5E866ACA

#include <chrono>
#include <cstdint>
#include <list>
#include "Value.h"

namespace HX711 {
class ValueStack {
protected:

    struct StackEntry {
        Value val;
        std::chrono::steady_clock::time_point when;
    };

    static const size_t _DEFAULT_MAX_SIZE = 80;
    static constexpr auto _DEFAULT_MAX_AGE = std::chrono::duration_cast
        <std::chrono::nanoseconds>(std::chrono::seconds(1));

    void _update();

    std::list<StackEntry> _container;
    std::size_t _maxSize;
    std::chrono::nanoseconds _maxAge;

public:

    ValueStack(
        const std::size_t maxSize = _DEFAULT_MAX_SIZE,
        const std::chrono::nanoseconds maxAge = _DEFAULT_MAX_AGE) noexcept;

    void push(const Value val) noexcept;
    Value pop() noexcept;
    std::size_t size() const noexcept;
    void clear() noexcept;
    bool empty() const noexcept;
    bool full() const noexcept;

};
};
#endif
