#include "batchloggroup.h"
#include "utils.h"
#include "util/thread_rwlock.h"

namespace tencent_log_sdk_cpp_v2
{

BatchLogGroup::BatchLogGroup(const std::string& topicid, const cls::Log& log) : attemptcount_(0), nextretryms_(0)
{
    auto clslog = loggroup_.add_logs();
    clslog->CopyFrom(log);
    createtimems_ = GetNowTimeMs();
    totaldatasize_ = 0;
    this->topicid_ = topicid;
}

void BatchLogGroup::setLogCallBack(std::shared_ptr<CallBack> callback)
{
    callback_ = callback;
}

std::string BatchLogGroup::getTopicID()
{
    return topicid_;
}

ErrCode BatchLogGroup::AddLogToLogGroup(const cls::Log& log)
{
    ThreadWLock lock(mutex_);
    auto logs = loggroup_.add_logs();
    logs->CopyFrom(log);
    return ErrCode{};
}

int BatchLogGroup::AddBatchSize(const int64_t datasize)
{
    totaldatasize_ += datasize;
    return totaldatasize_;
}

uint64_t BatchLogGroup::GetTotalDataSize()
{
    return totaldatasize_;
}
int64_t BatchLogGroup::GetCreateTimeMs()
{
    return createtimems_;
}


std::string BatchLogGroup::DebugString()
{
    std::stringstream ss;
    ss << "topic:" << topicid_ << " " /*<< loggroup_.ShortDebugString().c_str()*/;
    return ss.str();
}

cls::LogGroup BatchLogGroup::GetLogGroup()
{
    ThreadRLock lock(mutex_);
    return loggroup_;
}

void BatchLogGroup::CallBackReult(PostLogStoreLogsResponse ret)
{
    if (callback_ != NULL)
    {
        ret.statusCode == 200 ? callback_->Success(ret) : callback_->Fail(ret);
    }
}

void BatchLogGroup::CallBackMore5M(ErrCode res)
{
    if (callback_ != NULL)
    {
        PostLogStoreLogsResponse ret;
        ret.statusCode = res.retCode;
        ret.content = res.errMsg;
        callback_->Fail(ret);
    }
}

void BatchLogGroup::SetNextRetryMs(const int64_t nextretry)
{
    nextretryms_ = nextretry;
}

int64_t BatchLogGroup::GetNextRetryMs()
{
    return nextretryms_;
}

int BatchLogGroup::AdditionAttempt(const int attempt)
{
    attemptcount_ += attempt;
    return attemptcount_;
}

int BatchLogGroup::GetAttempt()
{
    return attemptcount_;
}


} // namespace tencent_log_sdk_cpp_v2
