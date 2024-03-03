// conveyor_status.cpp
#include "conveyor_status.hpp"

// ConveyorStatus::ConveyorStatus(MessageSender& sender) : messageSender(sender) {}
ConveyorStatus::ConveyorStatus() : messageSender(nullptr) {}

void ConveyorStatus::setMessageSender(MessageSender& sender) {
    messageSender = &sender;
}

void ConveyorStatus::changeConveyorStatus(int parameter) { // 添加 void 返回类型
    if (messageSender == nullptr) {
        // 处理未初始化 MessageSender 的情况
        return;
    }
    
    int newCounter = parameter;

    // 只有当newCounter的值与lastCounter不同时，才执行发送逻辑
    if (newCounter != lastCounter) {
        messageSender.sendMessage("conveyorStatus", {{"parameter", newCounter}});

        lastCounter = newCounter; // 更新lastCounter为当前的newCounter值
    }
}
