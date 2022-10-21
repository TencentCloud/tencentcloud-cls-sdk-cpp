#include "logthreadpool.h"
#include "utils.h"

#include <cmath>
#include <iostream>
#include <memory>
namespace tencent_log_sdk_cpp_v2
{
// the constructor just launches some amount of workers_
ThreadPool::ThreadPool(std::shared_ptr<LogMemMgr>& mgr, std::shared_ptr<LogRetryQueue>& retryqueue,
                       const cls_config::LogProducerConfig& config)
    : shutdownflag_(false), logmgr_(mgr), retryqueue_(retryqueue), config_(config)
{
    logclient_ = std::make_shared<LOGClient>(config_.endpoint(), config_.acceskeyid(), config_.accesskeysecret(),
                                             config.socktimeout(), config.connecttimeout(),config_.token(),config_.source(),
                                             config_.compressflag());
}

int ThreadPool::Start()
{
    for (size_t i = 0; i < config_.maxsendworkercount(); ++i)
        workers_.emplace_back(
                [this]
                {
                    for (;;)
                    {
                        std::shared_ptr<BatchLogGroup> batch;
                        {
                            std::unique_lock<std::mutex> lock(this->queuemutex_);
                            this->condition_.wait(lock,
                                                  [this] { return this->shutdownflag_ || !this->tasks_.empty(); });
                            if (this->shutdownflag_ && this->tasks_.empty())
                                return;
                            batch = std::move(this->tasks_.front());
                            this->tasks_.pop();
#ifdef Debug
                            std::cout << __FILE__ << __LINE__ << __FUNCTION__
                                      << "ThreadPool begin topicId: " << batch->getTopicID()
                                      << "||TotalDataSize:" << batch->GetTotalDataSize() << "||MemTotalSize"
                                      << logmgr_->GetMemTotalSize() << std::endl;
#endif
                            PostLogStoreLogsResponse ret
                                    = logclient_->PostLogStoreLogs(batch->getTopicID(), batch->GetLogGroup());
                            if (ret.statusCode == 200)
                            {
                                logmgr_->Subtraction(batch->GetTotalDataSize());
                                batch->CallBackReult(ret);
                            }
                            else if(ret.statusCode == 413 || ret.statusCode == 404 ||
                                    ret.statusCode == 401 || curl_errcode.count(ret.statusCode))
                            {
                                _DoProcessCallback(ret,batch);
                            }
                            else
                            {
                                if (batch->GetAttempt() < config_.retries())
                                {
                                    batch->AdditionAttempt(1);
                                    uint64_t retryWaitTime
                                            = config_.baseretrybackoffms() + std::pow(2, batch->GetAttempt());

                                    retryWaitTime < config_.maxretrybackoffms()
                                            ? (batch->SetNextRetryMs(GetNowTimeMs() + retryWaitTime))
                                            : (batch->SetNextRetryMs(GetNowTimeMs() + config_.maxretrybackoffms()));
                                    ErrCode res = retryqueue_->SendToRetryQueue(batch);
                                    if (res.retCode != 0)
                                    {
                                        ret.content = res.errMsg;
                                        _DoProcessCallback(ret,batch);
                                    }
                                }
                                else
                                {
                                    _DoProcessCallback(ret,batch);
                                }
                            }
#ifdef Debug
                            std::cout << __FILE__ << __LINE__ << __FUNCTION__
                                      << "ThreadPool end topicId: " << batch->getTopicID()
                                      << "||TotalDataSize:" << batch->GetTotalDataSize() << "||MemTotalSize"
                                      << logmgr_->GetMemTotalSize() <<"|| nextretryms_"<<batch->GetNextRetryMs()<<"ret:"<<ret.Printf()<< std::endl;
#endif
                        }
                    }
                });
    return 0;
}

void ThreadPool::_DoProcessCallback(PostLogStoreLogsResponse ret,std::shared_ptr<BatchLogGroup> batch)
{
    logmgr_->Subtraction(batch->GetTotalDataSize());
    ret.loggroup_.CopyFrom(batch->GetLogGroup());
    batch->CallBackReult(ret);
}

ErrCode ThreadPool::Enqueue(std::shared_ptr<BatchLogGroup> batch)
{
    if (shutdownflag_)
    {
        return ErrCode{ERR_CLS_SDK_TASK_SHUTDOWN, "task has shutdownflag_ and cannot retry"};
    }

    {
        std::unique_lock<std::mutex> lock(queuemutex_);
        tasks_.emplace(batch);
        condition_.notify_one();
    }

    return ErrCode{};
}

ThreadPool::~ThreadPool()
{
    shutdownflag_ = true;
    {
        condition_.notify_all();
        for (std::thread& worker : workers_)
        {
            if (worker.joinable())
            {
                worker.join();
            }
        }
    }
}

void ThreadPool::LogThreadPoolDestroy()
{
    shutdownflag_ = true;
    {
        condition_.notify_all();
        for (std::thread& worker : workers_)
        {
            if (worker.joinable())
            {
                worker.join();
            }
        }
    }
}
} // namespace tencent_log_sdk_cpp_v2
