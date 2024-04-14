#ifndef HX711_SCALE_H_5E9DF993_BC93_4934_A844_98355F4F8062
#define HX711_SCALE_H_5E9DF993_BC93_4934_A844_98355F4F8062

#include <chrono>
#include <cstdint>
#include <vector>
#include "Mass.h"
#include "Value.h"

namespace HX711 {

enum class StrategyType : unsigned char {
    Samples,
    Time
};

enum class ReadType : unsigned char {
    Median,
    Average
};

struct Options {
protected:
    static const std::size_t _DEFAULT_SAMPLE_COUNT = 3;

public:
    StrategyType stratType;
    ReadType readType;
    std::size_t samples;
    std::chrono::nanoseconds timeout;

    Options() noexcept;

    //cppcheck-suppress noExplicitConstructor
    Options(const std::size_t s, const ReadType rt = ReadType::Median) noexcept;

    //cppcheck-suppress noExplicitConstructor
    Options(const std::chrono::nanoseconds t, const ReadType rt = ReadType::Median) noexcept;

};

class AbstractScale {

protected:
    Mass::Unit _massUnit;
    Value _refUnit;
    Value _offset;

public:
    AbstractScale(
        const Mass::Unit massUnit,
        const Value refUnit,
        const Value offset) noexcept;

    void setUnit(const Mass::Unit unit) noexcept;
    Mass::Unit getUnit() const noexcept;

    Value getReferenceUnit() const noexcept;
    void setReferenceUnit(const Value refUnit);

    Value getOffset() const noexcept;
    void setOffset(const Value offset) noexcept;

    double normalise(const double v) const noexcept;

    virtual std::vector<Value> getValues(const std::size_t samples) = 0;
    virtual std::vector<Value> getValues(const std::chrono::nanoseconds timeout) = 0;

    double read(const Options o = Options());
    void zero(const Options o = Options());
    Mass weight(const Options o = Options());

    Mass weight(const std::chrono::nanoseconds timeout);
    Mass weight(const std::size_t samples);

};
};
#endif
