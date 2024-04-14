#ifndef HX711_VALUE_H_48F704C7_6B2D_4BEC_9599_62045594695B
#define HX711_VALUE_H_48F704C7_6B2D_4BEC_9599_62045594695B

#include <cmath>
#include <cstdint>

namespace HX711 {

/**
 * typedef for type to hold at least 24 bits
 * as per HX711 spec
 * TODO: would std::int_least32_t be more appropriate?
 */
typedef std::int32_t val_t;

class Value {

protected:

    val_t _v;

    /**
     * Datasheet pg. 3
     * But also a consequence of the sensor being 24 bits
     */
    static constexpr val_t _MIN = -static_cast<val_t>(std::pow(2, 24 - 1));
    static constexpr val_t _MAX = static_cast<val_t>(std::pow(2, 24 - 1)) - 1;


public:

    /**
     * Saturation values
     */
    static const val_t SATURATION_MIN = 0x800000;
    static const val_t SATURATION_MAX = 0x7FFFFF;

    /**
     * When input differential signal goes out of
     * the 24 bit range, the output data will be saturated
     * at 800000h (MIN) or 7FFFFFh (MAX), until the
     * input signal comes back to the input range.
     * Datasheet pg. 4
     */
    bool isSaturated() const noexcept;
    bool isMinSaturated() const noexcept;
    bool isMaxSaturated() const noexcept;

    /**
     * A 32 bit integer holds the actual value from the sensor. Calling
     * this function makes sure it is within the 24 bit range used by
     * the sensor.
     */
    bool isValid() const noexcept;
    operator val_t() const noexcept;
    
    //cppcheck-suppress noExplicitConstructor
    Value(const val_t v) noexcept;
    Value() noexcept;
    Value& operator=(const Value& v2) noexcept;

};
};
#endif
