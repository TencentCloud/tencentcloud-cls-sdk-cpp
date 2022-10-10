#ifndef __LOGV6_LOGTIIMER_H__
#define __LOGV6_LOGTIIMER_H__
#include "logthreadpool.h"
#include "logaccumulator.h"

namespace tencent_log_sdk_cpp_v2
{
class LogTimer
{
public:
    LogTimer(std::shared_ptr<LogAccumulator>& logaccumulator, std::shared_ptr<ThreadPool>& threadpool,
             std::shared_ptr<LogRetryQueue>& retryqueue, const cls_config::LogProducerConfig& config);
    ~LogTimer();

    void Start();

    void LogTimerDestroy();

private:
    void _TimerStart();

private:
    std::atomic_bool shutdownflag_;
    std::shared_ptr<LogAccumulator> logaccumulator_;
    std::shared_ptr<ThreadPool> threadpool_;
    mutable ThreadRWLocker mutex_;

    std::thread td_;

    const cls_config::LogProducerConfig& config_;

    std::shared_ptr<LogRetryQueue> retryqueue_;
};
} // namespace tencent_log_sdk_cpp_v2

#endif