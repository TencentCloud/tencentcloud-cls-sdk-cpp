#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

#include "batchloggroup.h"
#include "logmemmgr.h"
#include "logproducerconfig.pb.h"
#include "client.h"
#include "logretryqueue.h"
namespace tencent_log_sdk_cpp_v2
{
class ThreadPool
{
public:
    ThreadPool(std::shared_ptr<LogMemMgr>& mgr, std::shared_ptr<LogRetryQueue>& retryqueue,
               const cls_config::LogProducerConfig& config);
    ErrCode Enqueue(std::shared_ptr<BatchLogGroup> batch);
    ~ThreadPool();
    int Start();
    void LogThreadPoolDestroy();

private:
    void _DoProcessCallback(PostLogStoreLogsResponse ret,std::shared_ptr<BatchLogGroup> batch);
private:
    std::vector<std::thread> workers_;
    std::queue<std::shared_ptr<BatchLogGroup>> tasks_;
    std::mutex queuemutex_;
    std::condition_variable condition_;
    std::atomic_bool shutdownflag_;
    std::shared_ptr<LogMemMgr> logmgr_;
    std::shared_ptr<LogRetryQueue> retryqueue_;
    const cls_config::LogProducerConfig& config_;
    std::shared_ptr<LOGClient> logclient_;
};
} // namespace tencent_log_sdk_cpp_v2

#endif
