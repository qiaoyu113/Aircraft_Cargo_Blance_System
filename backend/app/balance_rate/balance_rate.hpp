// balance_rate.hpp

#ifndef BALANCE_RATE_H
#define BALANCE_RATE_H

class BalanceRate {
public:
    BalanceRate();
    void changeBalanceRate(int parameter); 

private:
    int lastCounter = 0; 
};

#endif // BALANCE_RATE_HPP