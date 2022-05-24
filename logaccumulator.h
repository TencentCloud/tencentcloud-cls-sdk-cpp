#ifndef __LOGV6_LOGACCUMULATOR_H__
#define __LOGV6_LOGACCUMULATOR_H__

#include <atomic>
#include <boost/thread/shared_mutex.hpp>
#include <map>
#include <unordered_map>
#include <string>

#include "logthreadpool.h"
#include "batchloggroup.h"
#include "error.h"

namespace tencent_log_sdk_cpp_v2
{
class LogAccumulator
{
public:
    mutable boost::shared_mutex mutex_;
    LogAccumulator(std::shared_ptr<ThreadPool>& threadpool, std::shared_ptr<LogMemMgr>& mgr,
                   const cls_config::LogProducerConfig& config);
    ~LogAccumulator();
    LogAccumulator(const LogAccumulator&) = delete;
    ErrCode AddLogToProducerBatch(const std::string& topicId, const cls::Log& log, std::shared_ptr<CallBack>& callback);
    std::unordered_map<std::string, std::shared_ptr<BatchLogGroup>> GetlogTopicData();
    ErrCode CreateBatchLogGroup(const std::string& topicId, const cls::Log& log, std::shared_ptr<CallBack> &callback,
                    const int64_t logsize);
    ErrCode AddTask(const std::string& topicId, std::shared_ptr<BatchLogGroup> batch);
    void LogAccumulatorDestroy();

private:
    std::unordered_map<std::string, std::shared_ptr<BatchLogGroup>> logtopicdata_;
    const cls_config::LogProducerConfig& config_;
    std::atomic_bool shutdownflag_;
    std::shared_ptr<ThreadPool> threadpool_;
    std::shared_ptr<LogMemMgr> logmgr_;
};
} // namespace tencent_log_sdk_cpp_v2

#endif