#ifndef __LOGV6_SDK_BATCHLOGGROUP_H__
#define __LOGV6_SDK_BATCHLOGGROUP_H__

#include "cls_logs.pb.h"
#include "result.h"

#include <string>
#include <mutex>
#include <vector>
#include <memory>
#include <thread>
#include "error.h"
#include <atomic>
#include "util/thread_rwlock.h"

namespace tencent_log_sdk_cpp_v2
{

class BatchLogGroup
{
public:
    BatchLogGroup(const std::string& topicid, const cls::Log& log);
    ~BatchLogGroup() {}
    std::string getTopicID();
    ErrCode AddLogToLogGroup(const cls::Log& log);
    cls::LogGroup GetLogGroup();
    int AddBatchSize(const int64_t datasize);
    uint64_t GetTotalDataSize();
    int64_t GetCreateTimeMs();
    std::string DebugString();
    void setLogCallBack(std::shared_ptr<CallBack> callback);
    void CallBackReult(PostLogStoreLogsResponse ret);
    void CallBackMore5M(ErrCode res);
    void SetNextRetryMs(const int64_t nextretry);
    int64_t GetNextRetryMs();

    int AdditionAttempt(int attempt);
    int GetAttempt();

private:
    std::atomic<std::uint64_t> totaldatasize_;
    mutable ThreadRWLocker mutex_;
    cls::LogGroup loggroup_;
    std::atomic<std::uint64_t> createtimems_;
    std::string topicid_;
    std::shared_ptr<CallBack> callback_;
    std::atomic<std::uint64_t> attemptcount_;
    std::atomic<std::uint64_t> nextretryms_;
};
} // namespace tencent_log_sdk_cpp_v2

#endif
