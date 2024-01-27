#include "logretryqueue.h"
#include "utils.h"
#include "util/thread_rwlock.h"

namespace tencent_log_sdk_cpp_v2
{
LogRetryQueue::LogRetryQueue() : shutdownflag_(false) {}
ErrCode LogRetryQueue::SendToRetryQueue(std::shared_ptr<BatchLogGroup>& batch)
{
    if (shutdownflag_)
    {
        return ErrCode{ERR_CLS_SDK_TASK_SHUTDOWN, "task has shutdownflag_ and cannot retry"};
    }

    if (batch != NULL)
    {
        ThreadWLock lock(mutex_);
        retrybatchqueue_.push(batch);
    }

    return ErrCode{};
}

std::vector<std::shared_ptr<BatchLogGroup>> LogRetryQueue::GetRetryBatch()
{
    ThreadWLock lock(mutex_);
    std::vector<std::shared_ptr<BatchLogGroup>> vecBatch;
    if (shutdownflag_)
    {
        for (; !retrybatchqueue_.empty(); retrybatchqueue_.pop())
        {
            vecBatch.emplace_back(retrybatchqueue_.top());
        }
    }
    else
    {
        for (; !retrybatchqueue_.empty(); retrybatchqueue_.pop())
        {
            auto pBatch = retrybatchqueue_.top();

            if (pBatch->GetNextRetryMs() > GetNowTimeMs())
            {
                break;
            }
            vecBatch.emplace_back(pBatch);
        }
    }
    return vecBatch;
}

void LogRetryQueue::LogRetryQueueDestroy()
{
    shutdownflag_ = true;
}
} // namespace tencent_log_sdk_cpp_v2
