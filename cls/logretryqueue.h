#ifndef __LOGV6_LOGRETRYQUEUE_H__
#define __LOGV6_LOGRETRYQUEUE_H__
#include <string>
#include <mutex>
#include <vector>
#include <queue>
#include <list>
#include <iostream>
#include <vector>

#include "util/thread_rwlock.h"
#include "batchloggroup.h"

namespace tencent_log_sdk_cpp_v2
{
struct BatchCmp
{

    bool operator()(const std::shared_ptr<BatchLogGroup>& batch1, const std::shared_ptr<BatchLogGroup>& batch2)
    {
        return batch1->GetNextRetryMs() > batch2->GetNextRetryMs();
    }
};
class LogRetryQueue
{
public:
    LogRetryQueue();
    ~LogRetryQueue() = default;
    ErrCode SendToRetryQueue(std::shared_ptr<BatchLogGroup>& batch);
    std::vector<std::shared_ptr<BatchLogGroup>> GetRetryBatch();
    void LogRetryQueueDestroy();

private:
    std::priority_queue<std::shared_ptr<BatchLogGroup>, std::vector<std::shared_ptr<BatchLogGroup>>, BatchCmp>
            retrybatchqueue_;
    mutable ThreadRWLocker mutex_;
    std::atomic_bool shutdownflag_;
};
} // namespace tencent_log_sdk_cpp_v2


#endif