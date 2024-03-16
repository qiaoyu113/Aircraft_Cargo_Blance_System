/**
 * @file   balance_rate.cpp
 * @brief  The calculated balance value is sent to the server
 *
 * @author Yu Qiao
 * @date   2024-02-22
 *
 * Additional notes:
 * - ...
 */

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