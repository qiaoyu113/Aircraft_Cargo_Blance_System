// conveyor_status.cpp
#include "conveyor_status.hpp"

ConveyorStatus::ConveyorStatus(MessageSender& sender) : messageSender(sender) {}

void ConveyorStatus::changeConveyorStatus(int parameter) { // 添加 void 返回类型
    int newCounter = parameter;

    // 只有当newCounter的值与lastCounter不同时，才执行发送逻辑
    if (newCounter != lastCounter) {
        messageSender.sendMessage("conveyorStatus", {{"parameter", newCounter}});

        lastCounter = newCounter; // 更新lastCounter为当前的newCounter值
    }
}
