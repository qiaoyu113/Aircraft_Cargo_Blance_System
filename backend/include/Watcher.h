#ifndef HX711_WATCHER_H_CFBFD856_ADA7_4F6A_9D3E_B7F6D39527D5
#define HX711_WATCHER_H_CFBFD856_ADA7_4F6A_9D3E_B7F6D39527D5

#include <chrono>
#include <mutex>
#include <pthread.h>
#include <sched.h>
#include "HX711.h"
#include "Value.h"
#include "ValueStack.h"

namespace HX711 {

enum class WatchState : unsigned char {
    NONE,
    NORMAL,
    PAUSE,
    END
};

class Watcher {

protected:

    static const int _PINWATCH_SCHED_POLICY = SCHED_FIFO;
    
    static constexpr auto _DEFAULT_PAUSE_SLEEP = std::chrono::duration_cast
        <std::chrono::nanoseconds>(std::chrono::milliseconds(100));

    static constexpr auto _DEFAULT_POLL_SLEEP = std::chrono::duration_cast
        <std::chrono::nanoseconds>(std::chrono::milliseconds(10));
    
    static constexpr auto _DEFAULT_NOT_READY_SLEEP = std::chrono::duration_cast
        <std::chrono::nanoseconds>(std::chrono::microseconds(7));

    HX711* const _hx;
    WatchState _watchState;
    std::mutex _pinWatchLock;
    pthread_t _watchThreadId;
    std::chrono::nanoseconds _pauseSleep;
    std::chrono::nanoseconds _notReadySleep;
    std::chrono::nanoseconds _pollSleep;

    static void* _watchPin(void* const watcherPtr);
    void _changeWatchState(const WatchState state);
    void _recoverHX711(const std::chrono::nanoseconds maxWait);


public:
    ValueStack values;
    std::mutex valuesLock;
    explicit Watcher(HX711* const hx) noexcept;
    ~Watcher();
    void begin();
    void watch();
    void pause();

};
};
#endif
