#ifndef HX711_ADVANCEDHX711_H_16C895F6_FD48_4E45_B690_97EFE239A14E
#define HX711_ADVANCEDHX711_H_16C895F6_FD48_4E45_B690_97EFE239A14E

#include <chrono>
#include <cstdint>
#include "AbstractScale.h"
#include "HX711.h"
#include "Value.h"
#include "Watcher.h"

namespace HX711 {
class AdvancedHX711 : public AbstractScale, public HX711 {

protected:
    Watcher* _wx;

public:
    AdvancedHX711(
        const int dataPin,
        const int clockPin,
        const Value refUnit = 1,
        const Value offset = 0,
        const Rate rate = Rate::HZ_10);

    virtual ~AdvancedHX711();

    virtual std::vector<Value> getValues(const std::chrono::nanoseconds timeout) override;
    virtual std::vector<Value> getValues(const std::size_t samples) override;

};
};
#endif
