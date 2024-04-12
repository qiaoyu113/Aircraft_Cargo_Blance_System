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

// balance_rate.cpp
#include "balance_rate.hpp"

BalanceRate::BalanceRate() : messageSender() {}

void BalanceRate::changeBalanceRate(int parameter) {
    int newCounter = parameter;

    // The send logic is executed only if the value of newCounter differs from lastCounter
    if (newCounter != lastCounter) {
        messageSender.sendMessage("balanceRate", newCounter);

        lastCounter = newCounter; // Update lastCounter to its current value of newCounter
    }
}
