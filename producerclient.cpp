#include "producerclient.h"

namespace tencent_log_sdk_cpp_v2
{
ProducerClient::ProducerClient(cls_config::LogProducerConfig& config) : config_(config)
{
    _ValidateProducerConfig();
    logmgr_ = std::make_shared<LogMemMgr>();
    retryqueue_ = std::make_shared<LogRetryQueue>();
    threadpool_ = std::make_shared<ThreadPool>(logmgr_, retryqueue_, this->config_);
    accumuloter_ = std::make_shared<LogAccumulator>(threadpool_, logmgr_, this->config_);
    logtimer_ = std::make_shared<LogTimer>(accumuloter_, threadpool_, retryqueue_, this->config_);
}
PostLogStoreLogsResponse ProducerClient::PostLogStoreLogs(const std::string& topic, const cls::Log& log,
                                                          std::shared_ptr<CallBack> callback)
{
    PostLogStoreLogsResponse ret;
    if (topic.empty())
    {
        ret.statusCode = ERR_CLS_SDK_PARAM_ERROR;
        ret.content = "topic is null ";
        return ret;
    }

    ErrCode err = _WaitTime();
    if (err.retCode != 0)
    {
        ret.statusCode = err.retCode;
        ret.content = err.errMsg;
        return ret;
    }


    err = accumuloter_->AddLogToProducerBatch(topic, log, callback);
    if (err.retCode != 0)
    {
        ret.statusCode = err.retCode;
        ret.content = err.errMsg;
    }
    return ret;
}

ErrCode ProducerClient::_WaitTime()
{
    if (config_.maxblocksec() < 0)
    {
        for (;;)
        {
            if (logmgr_->GetMemTotalSize() > config_.totalsizelnbytes())
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            else
            {
                return ErrCode{};
            }
        }
    }
    else if (config_.maxblocksec() == 0)
    {
        if (logmgr_->GetMemTotalSize() > config_.totalsizelnbytes())
        {
            return ErrCode{ERR_CLS_SDK_TOTALSIZELNBYTES_LIMIT, "TotalSizeLnBytes limit"};
        }
        else
        {
            return ErrCode{};
        }
    }
    else
    {
        for (int i = 0; i < config_.maxblocksec(); ++i)
        {
            if (logmgr_->GetMemTotalSize() > config_.totalsizelnbytes())
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            else
            {
                return ErrCode{};
            }
        }
    }

    return ErrCode{ERR_CLS_SDK_TOTALSIZELNBYTES_LIMIT, "TotalSizeLnBytes limit"};
}

void ProducerClient::Start()
{
    threadpool_->Start();
    logtimer_->Start();
}

void ProducerClient::LogProducerEnvDestroy()
{
    accumuloter_->LogAccumulatorDestroy();
    retryqueue_->LogRetryQueueDestroy();
    logtimer_->LogTimerDestroy();
    threadpool_->LogThreadPoolDestroy();
    google::protobuf::ShutdownProtobufLibrary();
}

void ProducerClient::_ValidateProducerConfig()
{
    if (config_.totalsizelnbytes() <= 0)
    {
        config_.set_totalsizelnbytes(100 * 1024 * 1024);
    }

    if (config_.maxsendworkercount() <= 0)
    {
        config_.set_maxsendworkercount(50);
    }

    if (config_.maxbatchsize() > 1024 * 1024 * 5 || config_.maxbatchsize() <= 0)
    {
        config_.set_maxbatchsize(1024 * 1024 * 5);
    }

    if (config_.lingerms() < 100)
    {
        config_.set_lingerms(2000);
    }

    if (config_.baseretrybackoffms() <= 0)
    {
        config_.set_baseretrybackoffms(100);
    }

    if (config_.maxretrybackoffms() <= 0)
    {
        config_.set_maxretrybackoffms(50 * 1000);
    }
}
} // namespace tencent_log_sdk_cpp_v2
