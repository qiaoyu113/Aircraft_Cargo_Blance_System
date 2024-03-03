// balance_rate.hpp

#ifndef BALANCE_RATE_H
#define BALANCE_RATE_H

#include "../../socket/send_message.hpp"

class BalanceRate {
public:
    BalanceRate(MessageSender& sender);
    void changeBalanceRate(int parameter); 

private:
    MessageSender& messageSender; 
    int lastCounter = 0; 
};

#endif // BALANCE_RATE_HPP