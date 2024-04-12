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

    // 只有当newCounter的值与lastCounter不同时，才执行发送逻辑
    if (newCounter != lastCounter) {
        messageSender.sendMessage("balanceRate", newCounter);

        lastCounter = newCounter; // 更新lastCounter为当前的newCounter值
    }
}
