#include "logaccumulator.h"
#include "utils.h"
#include "batchloggroup.h"
#include "adapter.h"
#include <atomic>
#include <list>
#include <string>
#include <boost/thread/shared_mutex.hpp>
#include "logretryqueue.h"
namespace tencent_log_sdk_cpp_v2
{
LogAccumulator::LogAccumulator(std::shared_ptr<ThreadPool>& threadpool, std::shared_ptr<LogMemMgr>& mgr,
                               const cls_config::LogProducerConfig& config)
    : threadpool_(threadpool), logmgr_(mgr), config_(config)
{
}

LogAccumulator::~LogAccumulator()
{
    shutdownflag_ = true;
}

ErrCode LogAccumulator::CreateBatchLogGroup(const std::string& topicId, const cls::Log& log, std::shared_ptr<CallBack> &callback,const int64_t logsize)
{
#ifdef Debug
    std::cout << __FILE__ << __LINE__ << __FUNCTION__ << "CreateBatchLogGroup begin topicId: " << topicId
              << /*" log:" << log.ShortDebugString()<< */std::endl;
#endif
    auto pBatchGroup = std::make_shared<BatchLogGroup>(topicId, log);
    pBatchGroup->setLogCallBack(callback);
    pBatchGroup->AddBatchSize(logsize);
    logmgr_->AddLogMemSize(logsize);
    logtopicdata_.insert(std::pair<std::string, std::shared_ptr<BatchLogGroup>>(topicId, pBatchGroup));
#ifdef Debug
    std::cout << __FILE__ << __LINE__ << __FUNCTION__ << "CreateBatchLogGroup end topicId: " << topicId
              << " log:" /*<< log.ShortDebugString()*/<< "GetTotalDataSize():"<<pBatchGroup->GetTotalDataSize()
              <<"GetMemTotalSize:"<<logmgr_->GetMemTotalSize()<<std::endl;
#endif
    return ErrCode{};
}

ErrCode LogAccumulator::AddLogToProducerBatch(const std::string& topicId, const cls::Log& log, std::shared_ptr<CallBack> &callback)
{
#ifdef Debug
    std::cout << __FILE__ << __LINE__ << __FUNCTION__ << "AddLogToProducerBatch begin topicId: " << topicId
              << /*" log:" << log.ShortDebugString()<<*/ std::endl;
#endif
    if (shutdownflag_)
    {
        return ErrCode{ERR_CLS_SDK_TASK_SHUTDOWN, "task has shutdownflag_ and cannot write to new logs"};
    }
    std::unique_lock<boost::shared_mutex> lock(mutex_);
    int64_t logsize = 0;
    ErrCode ret = GetLogContentSize(log,logsize);
    if (ret.retCode != 0)
    {
#ifdef Debug
        std::cout << __FILE__ << __LINE__ << __FUNCTION__ << "GetLogContentSize return Error topicId: " << topicId
                    << " retcode:" << ret.retCode << std::endl;
#endif
        return ret;
    }
    if (logtopicdata_.find(topicId) != logtopicdata_.end())
    {
#ifdef Debug
    std::cout << __FILE__ << __LINE__ << __FUNCTION__ << "AddLogToProducerBatch find topicId: " << topicId
              << " log:" /*<< log.ShortDebugString()*/<< "GetTotalDataSize():"<<
              logtopicdata_[topicId]->GetTotalDataSize()
              <<"GetMemTotalSize:"<<logmgr_->GetMemTotalSize()<<std::endl;
#endif
        int totaldatasize = logtopicdata_[topicId]->GetTotalDataSize() + logsize;
        auto logscount = logtopicdata_[topicId]->GetLogGroup().logs_size();
        if (totaldatasize > config_.maxbatchsize() && totaldatasize < 5242880 && logscount < 10000)
        {
            logmgr_->AddLogMemSize(logsize);
            logtopicdata_[topicId]->AddBatchSize(logsize);
            logtopicdata_[topicId]->AddLogToLogGroup(log);
            ret = AddTask(topicId, logtopicdata_[topicId]);
            if (ret.retCode != 0)
            {
                return ret;
            }
#ifdef Debug
    std::cout << __FILE__ << __LINE__ << __FUNCTION__ << "AddLogToProducerBatch find topicId: otaldatasize > config_.maxbatchsize() && totaldatasize < 5242880 && logscount < 10000" << topicId
              << /*" log:" << log.ShortDebugString()<< */"GetTotalDataSize():"<<
              totaldatasize
              <<"GetMemTotalSize:"<<logmgr_->GetMemTotalSize()<<std::endl;
#endif
        }
        else if (totaldatasize < config_.maxbatchsize() && logscount < 10000)
        {
            logmgr_->AddLogMemSize(logsize);
            logtopicdata_[topicId]->AddBatchSize(logsize);
            logtopicdata_[topicId]->AddLogToLogGroup(log);
#ifdef Debug
    std::cout << __FILE__ << __LINE__ << __FUNCTION__ << "AddLogToProducerBatch find topicId: totaldatasize < config_.maxbatchsize() && logscount < 10000" << topicId
              << /*" log:" << log.ShortDebugString()<< */"GetTotalDataSize():"<<
              logtopicdata_[topicId]->GetTotalDataSize()
              <<"GetMemTotalSize:"<<logmgr_->GetMemTotalSize()<<std::endl;
#endif
        }
        else
        {
            ErrCode ret = AddTask(topicId, logtopicdata_[topicId]);
            if (ret.retCode != 0)
            {
                return ret;
            }
            ret = CreateBatchLogGroup(topicId, log, callback,logsize);
            if (ret.retCode != 0)
            {
                return ret;
            }
        }
    }
    else
    {
        ret = CreateBatchLogGroup(topicId, log, callback,logsize);
        if (ret.retCode != 0)
        {
            return ret;
        }
    }
#ifdef Debug
    std::cout << __FILE__ << __LINE__ << __FUNCTION__ << "AddLogToProducerBatch end topicId: " << topicId << std::endl;
#endif
    return ret;
}

std::map<const std::string, std::shared_ptr<BatchLogGroup>> LogAccumulator::GetlogTopicData()
{
    return logtopicdata_;
}

ErrCode LogAccumulator::AddTask(const std::string& topicId, std::shared_ptr<BatchLogGroup> batch)
{
    threadpool_->Enqueue(batch);
    logtopicdata_.erase(topicId);
    return ErrCode{};
}

void LogAccumulator::LogAccumulatorDestroy()
{
    shutdownflag_ = true;
}

} // namespace tencent_log_sdk_cpp_v2
