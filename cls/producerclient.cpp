#include "producerclient.h"

namespace tencent_log_sdk_cpp_v2
{
#define LOG_GLOBAL_SSL (1<<0)
#define LOG_GLOBAL_WIN32 (1<<1)
#define LOG_GLOBAL_ALL (LOG_GLOBAL_SSL|LOG_GLOBAL_WIN32)
#define LOG_GLOBAL_NOTHING (0)
static uint32_t s_init_flag = 0;
static int s_last_result = 0;
ProducerClient::ProducerClient(cls_config::LogProducerConfig& config) : config_(config)
{
    _ValidateProducerConfig();
    logmgr_ = std::make_shared<LogMemMgr>();
    retryqueue_ = std::make_shared<LogRetryQueue>();
    threadpool_ = std::make_shared<ThreadPool>(logmgr_, retryqueue_, this->config_);
    accumuloter_ = std::make_shared<LogAccumulator>(threadpool_, logmgr_, this->config_);
    logtimer_ = std::make_shared<LogTimer>(accumuloter_, threadpool_, retryqueue_, this->config_);
}

int ProducerClient::_log_producer_env_init()
{
    if (s_init_flag == 1)
    {
        return s_last_result;
    }
    s_init_flag = 1;
    CURLcode ecode;
    if ((ecode = curl_global_init(LOG_GLOBAL_ALL)) != CURLE_OK)
    {
        s_last_result = 1;
    }
    else
    {
        s_last_result = 0;
    }
    return s_last_result;
}

void ProducerClient::_log_producer_env_destroy()
{
    if (s_init_flag == 0)
    {
        return;
    }
    s_init_flag = 0;
    curl_global_cleanup();
}
PostLogStoreLogsResponse ProducerClient::PostLogStoreLogs(const std::string& topic, const cls::Log& log,
                                                          std::shared_ptr<CallBack> callback)
{
    PostLogStoreLogsResponse ret;
    ret.statusCode = _log_producer_env_init();
    if(ret.statusCode != 0){
        return ret;
    }

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
    _log_producer_env_destroy();
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
