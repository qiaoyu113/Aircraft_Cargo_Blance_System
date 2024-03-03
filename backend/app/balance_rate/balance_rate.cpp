// balance_rate.cpp
#include "balance_rate.hpp"

BalanceRate::BalanceRate(MessageSender& sender) : messageSender(sender) {}

void BalanceRate::changeBalanceRate(int parameter) {
    int newCounter = parameter;

    // 只有当newCounter的值与lastCounter不同时，才执行发送逻辑
    if (newCounter != lastCounter) {
        messageSender.sendMessage("balanceRate", {{"parameter", newCounter}});

        lastCounter = newCounter; // 更新lastCounter为当前的newCounter值
    }
}
