#ifndef __LOGV6_PRODUCERCLIENT_H__
#define __LOGV6_PRODUCERCLIENT_H__
#include "result.h"
#include "cls_logs.pb.h"
#include "logthreadpool.h"
#include "logaccumulator.h"
#include "logtimer.h"
#include "logproducerconfig.pb.h"
#include "error.h"
#include "logretryqueue.h"

namespace tencent_log_sdk_cpp_v2
{
class ProducerClient
{
public:
    ProducerClient(cls_config::LogProducerConfig& config);
    PostLogStoreLogsResponse PostLogStoreLogs(const std::string& topic, const cls::Log& log, std::shared_ptr<CallBack> callback);

    void Start();

    void LogProducerEnvDestroy();


private:
    ErrCode _WaitTime();

    void _ValidateProducerConfig();

    int _log_producer_env_init();

    void _log_producer_env_destroy();

private:
    std::shared_ptr<ThreadPool> threadpool_;
    std::shared_ptr<LogAccumulator> accumuloter_;
    std::shared_ptr<LogTimer> logtimer_;
    std::shared_ptr<LogMemMgr> logmgr_;
    cls_config::LogProducerConfig& config_;
    std::shared_ptr<LogRetryQueue> retryqueue_;
};
} // namespace tencent_log_sdk_cpp_v2

#endif