#ifndef HX711_SIMPLEHX711_H_F776CAA5_D3AE_46D8_BD65_F4B3CD8E1DBA
#define HX711_SIMPLEHX711_H_F776CAA5_D3AE_46D8_BD65_F4B3CD8E1DBA

#include <cstdint>
#include <vector>
#include "AbstractScale.h"
#include "HX711.h"
#include "Value.h"

namespace HX711 {
class SimpleHX711 : public AbstractScale, public HX711 {
public:

    SimpleHX711(
        const int dataPin,
        const int clockPin,
        const Value refUnit = 1,
        const Value offset = 0,
        const Rate rate = Rate::HZ_10);

    virtual std::vector<Value> getValues(const std::chrono::nanoseconds timeout) override;
    virtual std::vector<Value> getValues(const std::size_t samples) override;
    //no override for waitReady; SimpleHX711 is based on busy-waiting

};
};
#endif
