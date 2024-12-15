#include "logtimer.h"
#include "utils.h"
#include "util/thread_rwlock.h"

#include <thread>

namespace tencent_log_sdk_cpp_v2
{
LogTimer::LogTimer(std::shared_ptr<LogAccumulator>& logaccumulator, std::shared_ptr<ThreadPool>& threadpool,
                   std::shared_ptr<LogRetryQueue>& retryqueue, const cls_config::LogProducerConfig& config)
    : logaccumulator_(logaccumulator), threadpool_(threadpool), retryqueue_(retryqueue), shutdownflag_(false),
      config_(config)
{
}

void LogTimer::_TimerStart()
{
    while (!shutdownflag_)
    {
        int64_t sleepMs = config_.lingerms();
        int64_t nowTimeMs = GetNowTimeMs();
        {

            ThreadWLock lock(mutex_);
            for (auto topicdata : logaccumulator_->GetlogTopicData())
            {
                int timeInterval = (topicdata.second)->GetCreateTimeMs() + config_.lingerms() - nowTimeMs;
                if (timeInterval < 0)
                {
                    ErrCode ret = logaccumulator_->AddTask(topicdata.first, topicdata.second);
                    if (ret.retCode != 0)
                    {
                        (topicdata.second)->CallBackMore5M(ret);
                        continue;
                    }
                }
                else
                {
                    if (sleepMs > timeInterval)
                    {
                        sleepMs = timeInterval;
                    }
                }
            }
        }
        auto vecRetryQueue = retryqueue_->GetRetryBatch();
        if (!vecRetryQueue.empty())
        {
            ThreadRLock lock(logaccumulator_->mutex_);
            for (auto pBatch : vecRetryQueue)
            {
                ErrCode ret = logaccumulator_->AddTask(pBatch->getTopicID(), pBatch);
                if (ret.retCode != 0)
                {
                    pBatch->CallBackMore5M(ret);
                    continue;
                }
            }
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));
        }
    }

    {
        ThreadRLock lock(logaccumulator_->mutex_);
        for (auto topicdata : logaccumulator_->GetlogTopicData())
        {
            ErrCode ret = logaccumulator_->AddTask(topicdata.first, topicdata.second);
            if (ret.retCode != 0)
            {
                (topicdata.second)->CallBackMore5M(ret);
                continue;
            }
        }
        for (auto pBatch : retryqueue_->GetRetryBatch())
        {
            ErrCode ret = logaccumulator_->AddTask(pBatch->getTopicID(), pBatch);
            if (ret.retCode != 0)
            {
                pBatch->CallBackMore5M(ret);
                continue;
            }
        }
    }
}

void LogTimer::Start()
{
    td_ = std::thread(&LogTimer::_TimerStart, this);
}

LogTimer::~LogTimer()
{
    shutdownflag_ = true;
    if (td_.joinable())
        td_.join();
}

void LogTimer::LogTimerDestroy()
{
    shutdownflag_ = true;
    if (td_.joinable())
        td_.join();
}

} // namespace tencent_log_sdk_cpp_v2