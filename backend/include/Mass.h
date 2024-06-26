#ifndef HX711_MASS_H_2FFE3D59_FB56_4C50_87F6_08F5AD88A303
#define HX711_MASS_H_2FFE3D59_FB56_4C50_87F6_08F5AD88A303

#include <cstdint>
#include <ostream>
#include <string>
#include <unordered_map>

namespace HX711 {
class Mass {
public:

enum class Unit : unsigned char {
    UG,
    MG,
    G,
    KG,
    TON,
    IMP_TON,
    US_TON,
    ST,
    LB,
    OZ
};

protected:

    /**
     * This needs to be a sufficient size to contain a floating point
     * number, space, and unit name. eg.
     * 
     * "39823.3801 ton (IMP)"
     */
    static const std::size_t _TOSTRING_BUFF_SIZE = 64;

    static const std::unordered_map<const Unit, const double> _RATIOS;
    static const std::unordered_map<const Unit, const char* const> _UNIT_NAMES;

    //deal with mass internally as micrograms
    double _ug;

    //unit the calling code has chosen to represent this Mass
    Unit _u;


public:
    Mass(const double amount = 0.0, const Unit u = Unit::UG) noexcept;
    Mass(const Mass& m2) noexcept;

    Mass& operator=(const Mass& rhs) noexcept;
    
    operator double() const noexcept;
    double getValue() const noexcept;
    double getValue(const Unit u) const noexcept;

    Unit getUnit() const noexcept;
    void setUnit(const Unit u) noexcept;

    Mass convertTo(const Unit to) const noexcept;

    friend Mass operator+(const Mass& lhs, const Mass& rhs) noexcept;
    friend Mass operator-(const Mass& lhs, const Mass& rhs) noexcept;
    friend Mass operator*(const Mass& lhs, const Mass& rhs) noexcept;
    friend Mass operator/(const Mass& lhs, const Mass& rhs);
    
    Mass& operator+=(const Mass& rhs) noexcept;
    Mass& operator-=(const Mass& rhs) noexcept;
    Mass& operator*=(const Mass& rhs) noexcept;
    Mass& operator/=(const Mass& rhs);

    friend bool operator==(const Mass& lhs, const Mass& rhs) noexcept;
    friend bool operator!=(const Mass& lhs, const Mass& rhs) noexcept;
    friend bool operator<(const Mass& lhs, const Mass& rhs) noexcept;
    friend bool operator>(const Mass& lhs, const Mass& rhs) noexcept;
    friend bool operator<=(const Mass& lhs, const Mass& rhs) noexcept;
    friend bool operator>=(const Mass& lhs, const Mass& rhs) noexcept;

    std::string toString() const noexcept;
    std::string toString(const Unit u) const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Mass& m) noexcept;

    static double convert(
        const double amount,
        const Unit from,
        const Unit to = Unit::UG) noexcept;

};
};
#endif